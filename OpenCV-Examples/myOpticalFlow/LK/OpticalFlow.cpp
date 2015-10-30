#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <armadillo>
#include <iomanip>



using namespace std;
using namespace arma;


static const double pi = 3.14159265358979323846;
inline static double square(int a)
{
return a * a;
}

//Change CmakeList - see at the bottom ;)
/*
int 
main(int argc, char** argv)
{
  cv::Mat img1;
  cv::Mat img2;
  
  img1 = cv::imread("001.tif", CV_LOAD_IMAGE_GRAYSCALE);
  img1 = cv::imread("002.tif", CV_LOAD_IMAGE_GRAYSCALE);
  
  cv::namedWindow("Image", CV_WINDOW_AUTOSIZE );
  cv::imshow("Image", img1);
  cv::waitKey();
  
  
  cv::Mat vel_x;
  vel_x.create( img1.rows, img1.cols, CV_32F);
  
  cv::Mat vel_y;
  vel_y.create( img1.rows, img1.cols, CV_32F);
  
  
  cv::calcOpticalFlowLK( img1, img2, cvSize(5, 5), vel_x, vel_y );
  
  }
  */



static void help()
{
  // print a welcome message, and the OpenCV version
  cout << "\nThis is a demo of Lukas-Kanade optical flow lkdemo(),\n"
  "Using OpenCV version " << CV_VERSION << endl;
  cout << "\nIt uses camera by default, but you can provide a path to video as an argument.\n";
  cout << "\nHot keys: \n"
  "\tESC - quit the program\n"
  "\tr - auto-initialize tracking\n"
  "\tc - delete all the points\n"
  "\tn - switch the \"night\" mode on/off\n"
  "To add/remove a feature point click it\n" << endl;
}

cv::Point2f point;

// bool addRemovePt = false;
// 
// static void onMouse( int event, int x, int y, int /*flags*/, void* /*param*/ )
// {
  //     if( event == CV_EVENT_LBUTTONDOWN )
  //     {
    //         point = cv::Point2f((float)x, (float)y);
    //         addRemovePt = true;
    //     }
    // }
    
    int main( int argc, char** argv )
    {
      help();
      
      cv::VideoCapture cap;
      cv::TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20, 0.03);
      cv::Size subPixWinSize(10,10), winSize(31,31);
      
      const int MAX_COUNT = 500;
      bool needToInit = false;
      bool nightMode = false;
      
      if( argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
	cap.open(argc == 2 ? argv[1][0] - '0' : 0);
      else if( argc == 2 )
	cap.open(argv[1]);
      
      if( !cap.isOpened() )
      {
	cout << "Could not initialize capturing...\n";
	return 0;
      }
      
      cv::namedWindow( "LK Demo", 1 );
      //cv::setMouseCallback( "LK Demo", onMouse, 0 );
      
      cv::Mat gray, prevGray, image;
      cv::vector<cv::Point2f> points[2];
      
      for(;;)
      {
	cv::Mat frame;
	cap >> frame;
	if( frame.empty() )
	  break;
	
	frame.copyTo(image);
	cv::cvtColor(image, gray, CV_BGR2GRAY);
	
	if( nightMode )
	  image = cv::Scalar::all(0);
	
	if( needToInit )
	{
	  // automatic initialization
	  cv::goodFeaturesToTrack(gray, points[1], MAX_COUNT, 0.01, 10, cv::Mat(), 3, 0, 0.04);
	  cv::cornerSubPix(gray, points[1], subPixWinSize, cv::Size(-1,-1), termcrit);
	  //addRemovePt = false;
	}
	else if( !points[0].empty() )
	{
	  vector<uchar> status;
	  vector<float> err;
	  if(prevGray.empty())
	    gray.copyTo(prevGray);
	  cv::calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err, winSize,
				   3, termcrit, 0, 0.001);
				                size_t i, k;
				                for( i = k = 0; i < points[1].size(); i++ )
				                {
// 				                      if( addRemovePt )
// 				                      {
// 				                            if( norm(point - points[1][i]) <= 5 )
// 				                           {
// 					                          addRemovePt = false;
// 					                          continue;
// 					                      }
// 					                  }
					  
					                  if( !status[i] )
					                      continue;
					  
					                  points[1][k++] = points[1][i];
					                  //circle( image, points[1][i], 3, cv::Scalar(0,255,0), -1, 8);
					              }
					              points[1].resize(k);
	for(int i = 0; i < MAX_COUNT; i++)
	{
	  /* If Pyramidal Lucas Kanade didn't really find the feature, skip it. */
	  if( !status[i] ) continue;
	  int line_thickness; line_thickness = 1;
	  /* CV_RGB(red, green, blue) is the red, green, and blue components
	  * of the color you want, each out of 255.
	  */
	  cv::Scalar line_color; line_color = CV_RGB(255,0,0);
	  /* Let's make the flow field look nice with arrows. */
	  /* The arrows will be a bit too short for a nice visualization because of the 
	  high framerate
	  * (ie: there's not much motion between the frames). So let's lengthen them 
	  by a factor of 3.
	  */
	  cv::Point p,q;
	  p.x = (int) points[0][i].x;
	  p.y = (int) points[0][i].y;
	  q.x = (int) points[1][i].x;
	  q.y = (int) points[1][i].y;
	  double angle; angle = atan2( (double) q.y - p.y, (double) q.x - p.x );
	  double hypotenuse; hypotenuse = sqrt( square(q.y - p.y) + square(q.x - p.x) )
	  ;
	  /* Here we lengthen the arrow by a factor of three. */
	  q.x = (int) (p.x - 3 * hypotenuse * cos(angle));
	  q.y = (int) (p.y - 3 * hypotenuse * sin(angle));
	  /* Now we draw the main line of the arrow. */
	  /* "frame1" is the frame to draw on.
	  * "p" is the point where the line begins.
	  * "q" is the point where the line stops.
	  * "CV_AA" means antialiased drawing.
	  * "0" means no fractional bits in the center cooridinate or radius.
	  */
	  cv::line( image, p, q, line_color, line_thickness, CV_AA, 0 );
	  /* Now draw the tips of the arrow. I do some scaling so that the
	  * tips look proportional to the main line of the arrow.
	  */
	  p.x = (int) (q.x + 9 * cos(angle + pi / 4));
	  p.y = (int) (q.y + 9 * sin(angle + pi / 4));
	  cv::line( image, p, q, line_color, line_thickness, CV_AA, 0 );
	  p.x = (int) (q.x + 9 * cos(angle - pi / 4));
	  p.y = (int) (q.y + 9 * sin(angle - pi / 4));
	  cv::line( image, p, q, line_color, line_thickness, CV_AA, 0 );
	}
	
	}
	
	//if( addRemovePt && points[1].size() < (size_t)MAX_COUNT )
	if(points[1].size() < (size_t)MAX_COUNT )
	{
	  vector<cv::Point2f> tmp;
	  tmp.push_back(point);
	  cornerSubPix( gray, tmp, winSize, cv::Size(-1,-1), termcrit);
	  points[1].push_back(tmp[0]);
	  //addRemovePt = false;
	}
	
	
	
	
	
	
	
	needToInit = false;
	cv::imshow("LK Demo", image);
	
	char c = (char)cv::waitKey(10);
	if( c == 27 )
	  break;
	switch( c )
	{
	  case 'r':
	    needToInit = true;
	    break;
	  case 'c':
	    points[0].clear();
	    points[1].clear();
	    break;
	  case 'n':
	    nightMode = !nightMode;
	    break;
	}
	
	std::swap(points[1], points[0]);
	cv::swap(prevGray, gray);
      }
      
      return 0;
    }
    
    