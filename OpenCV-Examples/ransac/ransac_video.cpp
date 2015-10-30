///Creating my Ransac. It didn't work with my optical features
///Ideas Usar una combinaciond e Optical Flow Features and ???
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <armadillo>
#include <iomanip>
#include <vector>

using namespace std;
using namespace arma;


uword row = 120;
uword col = 160;
uword dim =14;

inline void feature_video(std::string one_video);
inline cv::Mat feat_frame2opencv(std::vector < vec > feat_frame);
inline void testing_ransac(cv::Mat currDescriptor, cv::Mat  prevDescriptor, cv::Mat currframe, cv::Mat prevframe,  std::vector<cv::Point2f> currKeypoints, std::vector<cv::Point2f> prevKeypoints);


int
main(int argc, char** argv)
{
  
std::string video;
video = "person17_running_d1_uncomp.avi";
feature_video(video);
}




///See this
///http://docs.opencv.org/doc/tutorials/features2d/feature_homography/feature_homography.html


inline
cv::Mat
feat_frame2opencv(std::vector < vec > feat_frame)
{
  
  cv::Mat currDescriptor(feat_frame.size(),dim, CV_32FC1);
  //double tmp_vec[dim];
  
  for (uword i=0; i< feat_frame.size(); ++i)
  {
    vec tmp_vec = feat_frame.at(i);
    
    for (uword d = 0; d < dim; ++d)
    {
      currDescriptor.at<float>(i,d) = (float)tmp_vec(d); 
      
    }
    //current_descriptor.row(i) = cvMatConv;
    //cout << "currDescriptor.row(i) " << endl;
    //cout << currDescriptor.row(i) << endl; 
    //tmp_vec.t().print("");
    //getchar();
    
  }
  
  //cout << "Funciono" << endl;
  //getchar( );
  
  return currDescriptor;
  
}

inline 
void 
testing_ransac(cv::Mat currDescriptor, cv::Mat  prevDescriptor, cv::Mat currframe, cv::Mat prevframe,  std::vector<cv::KeyPoint> currKeypoints, std::vector<cv::KeyPoint> prevKeypoints)
{
    cv::FlannBasedMatcher matcher;
  std::vector< cv::DMatch > matches;
  matcher.match( currDescriptor, prevDescriptor, matches );
  
  double max_dist = 0; double min_dist = 100;

  //-- Quick calculation of max and min distances between keypoints
  
  for( int i = 0; i < currDescriptor.rows; i++ )
  { double dist = matches[i].distance;
    if( dist < min_dist ) min_dist = dist;
    if( dist > max_dist ) max_dist = dist;
  }

  printf("-- Max dist : %f \n", max_dist );
  printf("-- Min dist : %f \n", min_dist );

  //-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
  
  //Good matches is empty. I don't know why

  std::vector< cv::DMatch > good_matches;

  for( int i = 0; i < currDescriptor.rows; i++ )
  { if( matches[i].distance < max_dist ) //OJO
     { good_matches.push_back( matches[i]); }
  }

  

  cout << matches.size() << endl;
  cout << good_matches.size() << endl;
  
  cv::Mat img_matches;
  cv::drawMatches( currframe, currKeypoints, prevframe, prevKeypoints,
              matches, img_matches, cv::Scalar::all(-1), cv::Scalar::all(-1),
               vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

               
  //-- Localize the object
  
  
  std::vector<cv::Point2f> obj;
  std::vector<cv::Point2f> scene;

  
  for( int i = 0; i < good_matches.size(); i++ )
  {
    //-- Get the keypoints from the good matches
    obj.push_back( currKeypoints[ good_matches[i].trainIdx  ].pt );
    scene.push_back( prevKeypoints[ good_matches[i].queryIdx].pt );
  }

  
  //cv::Mat H = cv::findHomography( obj, scene, CV_RANSAC );
  
   //-- Get the corners from the image_1 ( the object to be "detected" )
  std::vector<cv::Point2f> obj_corners(4);
  obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( currframe.cols, 0 );
  obj_corners[2] = cvPoint( currframe.cols, prevframe.rows ); obj_corners[3] = cvPoint( 0, currframe.rows );
  std::vector<cv::Point2f> scene_corners(4);

  //perspectiveTransform( obj_corners, scene_corners, H);

  //-- Draw lines between the corners (the mapped object in the scene - image_2 )
  line( img_matches, scene_corners[0] + cv::Point2f( currframe.cols, 0), scene_corners[1] + cv::Point2f( currframe.cols, 0), cv::Scalar(0, 255, 0), 4 );
  line( img_matches, scene_corners[1] + cv::Point2f( currframe.cols, 0), scene_corners[2] + cv::Point2f( currframe.cols, 0), cv::Scalar( 0, 255, 0), 4 );
  line( img_matches, scene_corners[2] + cv::Point2f( currframe.cols, 0), scene_corners[3] + cv::Point2f( currframe.cols, 0), cv::Scalar( 0, 255, 0), 4 );
  line( img_matches, scene_corners[3] + cv::Point2f( currframe.cols, 0), scene_corners[0] + cv::Point2f( currframe.cols, 0), cv::Scalar( 0, 255, 0), 4 );

  
  //-- Show detected matches
  imshow( "Good Matches & Object detection", img_matches );

  cv::waitKey();
  
  
  
  
  
}


inline 
void
feature_video(std::string one_video)
{
  
  std::vector < vec > feat_frame;
  
  
  cv::VideoCapture capVideo(one_video);
  cout << one_video << endl;
  double fps = capVideo.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video
  //cout << "Frame per seconds : " << fps << endl;
  
  //cv::namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
  
  double frmcount = capVideo.get(CV_CAP_PROP_FRAME_COUNT);
  //cout << "# of frames is: " << frmcount << endl;
  
  if( !capVideo.isOpened() )
  {
    cout << "Video couldn't be opened" << endl;
    return;
  }
  
  cv::Mat prevgray, gray, flow, cflow, frame, prevflow, prevframe, currframe, currDescriptor, prevDescriptor;
  cv::Mat ixMat, iyMat, ixxMat, iyyMat;// str_pts, dst_pts;
  
  std::vector<cv::KeyPoint> currKeypoints;//str_pts
  std::vector<cv::KeyPoint> prevKeypoints; //dst_pts
  
  
  //cv::namedWindow("My Video", 1);
  //running_stat_vec<vec> stats_video(true);
  //cout << "Frame: ";
  int t = -1;
 
  
  
  for(uword fr=0; fr<frmcount; fr++){
    
    //cout << t << " " ;
    
    bool bSuccess = capVideo.read(frame); // read a new frame from video
    
    if (!bSuccess) //if not success, break loop
	{
	  //cout << "Cannot read the frame from video file" << endl;
	  break;
	}
	t++;
    
    
    cv::cvtColor(frame, gray, CV_BGR2GRAY);
    //cv::cvtColor(frame,gray, cv::COLOR_BGR2GRAY);//For Opencv 3.0 (installed at home)
    
  //cv::Size size = frame.size();
  //str_pts = cv::Mat::zeros(size, CV_8UC1);
  
  //dst_pts = cv::Mat::zeros(size, CV_8UC3);
  //dst_pts.setTo( cv::Scalar(0,0,0) );
  
  
   
    if( prevgray.data )
    {
      currframe = frame;
  
      cout << t << " " ;
      cv::calcOpticalFlowFarneback(prevgray, 
				   gray, 
				   flow, 
				   0.5, //pyr_scale
				   3,   //levels
				   9,   //winsize
				   1,   //iterations
				   5,   //poly_n
				   1.1, //poly_sigma
				   0);  //flags
      
      
      cv::Sobel(gray, ixMat, CV_32F, 1, 0, 1);
      cv::Sobel(gray, iyMat, CV_32F, 0, 1, 1);
      cv::Sobel(gray, ixxMat, CV_32F, 2, 0, 1);
      cv::Sobel(gray, iyyMat, CV_32F, 0, 2, 1);
      
      float  ux = 0, uy = 0, vx = 0,  vy = 0;
      float u, v;
      
      if( prevflow.data )
      {
	//str_pts.setTo( cv::Scalar(0) );
	currKeypoints.clear();
	
	for (uword x = 0 ; x < col ; ++x ){
	  for (uword y = 0 ; y < row ; ++y ) {
	    
	    vec features_one_pixel(14);
	    u = flow.at<cv::Vec2f>(y, x)[0];
	    v = flow.at<cv::Vec2f>(y, x)[1];
	    
	    //cout << "x= " << x << " - y= " << y << endl;
	    // x grad
	    //cout << " x y grad" << endl;
	    float ix = ixMat.at<float>(y, x);
	    //cout << " y grad" << endl;
	    float iy = iyMat.at<float>(y, x);
	    
	    // grad direction &  grad magnitude
	    //cout << "grad direction &  grad magnitude" << endl;
	    float gd = std::atan2(std::abs(iy), std::abs(ix));
	    float gm = std::sqrt(ix * ix + iy * iy);
	    
	    // x second grad
	    //cout << "x y  second grad " << endl;
	    float ixx = ixxMat.at<float>(y, x);
	    // y second grad
	    float iyy = iyyMat.at<float>(y, x);
	    
	    //du/dt
	    float ut = u - prevflow.at<cv::Vec2f>(y, x)[0];
	    // dv/dt
	    float vt = v - prevflow.at<cv::Vec2f>(y, x)[1];
	    
	    //// divergence &  vorticity
	    //cout << "divergence &  vorticity" << endl;
	    if (x>0 && y>0 )
	    {
	      ux = u - flow.at<cv::Vec2f>(y, x - 1)[0];
	      uy = u - flow.at<cv::Vec2f>(y - 1, x)[0];
	      vx = v - flow.at<cv::Vec2f>(y, x - 1)[1];
	      vy = v - flow.at<cv::Vec2f>(y - 1, x)[1];
	    }
	    


	    //int x_submat = x + rec.x;
	    //int y_submat = y + rec.y;
	    //cout << x_submat << "&" << y_submat << endl;
	    
	    
	    
	    features_one_pixel  << x << y << abs(ix) << abs(iy) << abs(ixx) 
	    << abs(iyy) << gm << gd <<  u << v << abs(ut) 
	    << abs(vt) << (ux - vy)  << (vx - uy);
	    //features_one_pixel.t().print("Features Current Pixel: ");
	    //getchar();
	    
	    
	    if (!is_finite( features_one_pixel ) )
	    {
	      cout << "It's not FINITE... continue???" << endl;
	      getchar(); 
	    }
	    // Plotting Moving pixels
	    //cout << " " << gm;
	    if (gm>40) // Empirically set to 40
			    {
			   
			      frame.at<cv::Vec3b>(y,x)[0] = 0;
			      frame.at<cv::Vec3b>(y,x)[1] = 0;
			      frame.at<cv::Vec3b>(y,x)[2] = 255;
			      
			      
			      //currKeypoints.at<unsigned char>(y,x) = 255;
			       
			      cv::Point2f point(y, x);
			      
			      
			      currKeypoints.push_back(cv::KeyPoint(point, 100.f));
			      
			      //currKeypoints.push_back(point);
			      
			     
			      
			      feat_frame.push_back(features_one_pixel);
			      
			     
			      
			      
			      string text;
			      std::stringstream tmp_ss;
			      tmp_ss << t;
			      text = tmp_ss.str();
			      int fontFace = cv::FONT_HERSHEY_PLAIN;
			      double fontScale = 2;
			      int thickness = 2;  
			      cv::Point textOrg(10, 100);
			      cv::putText(currframe, text, textOrg, fontFace, fontScale, cv::Scalar::all(0), thickness,8);
			       
			    }
			    
			    
	    
	  }
	  
	}
	
	
	 ///aqui convertir feat_frame a openCV Mat
	 
	 
	 currDescriptor = feat_frame2opencv(feat_frame);
	 
	 ///RANSAC
	 
	 
	 
	 
	 
	 if (prevframe.data && currframe.data)
	 {
	   //cout << "Donde entra: " << t << endl; 
	   cv::imshow("color", frame);
	   cv::imshow("previous", prevframe);    
	   cv::imshow("current", currframe);  
	   
	  
	   //cv::imshow("current_mask", str_pts); 
	   // cv::imshow("previous_mask", prevKeypoints);    
	   //std::swap(currframe, prevframe );  
	   cv::waitKey();
	   //cout << currKeypoints.size() << endl;	   
	   //cout << prevKeypoints.size() << endl;

	   
	   ///hacer funcion aqui... si otra :)
	   ///testing_ransac(currDescriptor, prevDescriptor);
	   cout << "RANSAC??"  << endl;
	   testing_ransac(currDescriptor, prevDescriptor, currframe, prevframe,  currKeypoints, prevKeypoints);

	   //cv::Mat mask = cv::findHomography(str_pts,dst_pts , cv::RANSAC,5.0);
	 }
	 
	 std::swap(prevframe, frame );   
	 std::swap(prevDescriptor, currDescriptor ); 
	 std::swap(currKeypoints, prevKeypoints ); 

	
      }
      
      //cv::Mat mask = cv::findHomography(prevframe,currframe , cv::RANSAC,5.0); 
      
  /*
    cv::imshow("color", frame);
    cv::imshow("previous", prevframe);    
    cv::imshow("current", currframe);  
    //std::swap(currframe, prevframe );  
    cv::waitKey();
	*/
       
    }
    
    if(cv::waitKey(30)>=0)
      break;
    
   
    std::swap(prevgray, gray);
    std::swap(prevflow, flow);

   // std::swap(currframe, prevframe );
    //

   //string text;

    
    /*
    int fontFace = cv::FONT_HERSHEY_PLAIN;
    double fontScale = 0.8;
    int thickness = 1;  
    cv::Point textOrg(10, 100);
    cv::putText(frame, text, textOrg, fontFace, fontScale, cv::Scalar::all(255), thickness,8);
    */
    //cout << "otro tam: " <<feat_video_i.size() << endl;
  
    
    //cv::imshow("color", frame);  
    //cv::imshow("mask",mask );

     //cv::waitKey();
    //
    
}    
  feat_frame.clear();
  getchar();
  


}