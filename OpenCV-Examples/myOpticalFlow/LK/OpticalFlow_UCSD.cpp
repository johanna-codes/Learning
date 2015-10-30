//This is the best code:
//Taken from: http://i-vizon.blogspot.com.au/2013/03/optical-flow-using-opencv-library-on.html


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include<stdio.h>
#include <math.h>

#include <fstream>
#include <armadillo>
#include <dirent.h>


using namespace arma;

using namespace arma;

//using namespace cv;
using namespace std;

#define MAX_COUNT 500
char rawWindow[] = "Raw Video";
char opticalFlowWindow[] = "Optical Flow Window";
char imageFileName[32];
long imageIndex = 0;
char keyPressed;

int main(int argc, char* argv[]) {
  
  
  //cv::VideoCapture cap;
  //if( argc == 2 )
  //  cap.open(argv[1]); 
  
  std::string path ="/home/johanna/codes-svn/dataset_ucsd_svn/f1_f2/";
  field<std::string> list;
  
  std::stringstream path_list;
  path_list << path << "list.txt";
  list.load(path_list.str());
  //list.print("list");
  //VideoCapture cap(0);
    
    cv::Mat frame, grayFrames, rgbFrames, prevGrayFrame;
    //cv::Mat opticalFlow = cv::Mat(cap.get(CV_CAP_PROP_FRAME_HEIGHT), cap.get(CV_CAP_PROP_FRAME_HEIGHT), CV_32FC3);
    cv::Mat opticalFlow = cv::Mat(48,84, CV_32FC3);///RE OJO!!!
    vector<cv::Point2f> points1;
    vector<cv::Point2f> points2;
    
    cv::Point2f diff;
    
    vector<uchar> status;
    vector<float> err;
    
    cv::RNG rng(12345);
    cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255),rng.uniform(0, 255));
    bool needToInit = true;
    
    int i, k;
    cv::TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
    cv::Size subPixWinSize(10, 10), winSize(31, 31);
    cv::namedWindow(rawWindow, CV_WINDOW_AUTOSIZE);
    double angle;
    
    
    for (uword fn=0; fn<list.n_rows; ++fn) {
      std::stringstream frame_name;
      frame_name << path << list(fn,0);
      cout << frame_name.str() << endl;
      frame = cv::imread(frame_name.str());
      frame.copyTo(rgbFrames);
      cv::cvtColor(rgbFrames, grayFrames, CV_BGR2GRAY);
      
      

      
      if (needToInit) {
	cv::goodFeaturesToTrack(grayFrames, points1, MAX_COUNT, 0.01, 5, cv::Mat(), 3, 0, 0.04);
	needToInit = false;
      } else if (!points2.empty()) {
	//cout << "\n\n\nCalculating  calcOpticalFlowPyrLK\n\n\n\n\n";
	cv::calcOpticalFlowPyrLK(prevGrayFrame, grayFrames, points2, points1, status, err, winSize, 3, termcrit, 0, 0.001);
	
	for (i = k = 0; i < points2.size(); i++) {
	  /*cout << "Optical Flow Difference... X is "
	  << int(points1[i].x - points2[i].x) << "\t Y is "
	  << int(points1[i].y - points2[i].y) << "\t\t" << i
	  << "\n";*/
	  
	  if ((points1[i].x - points2[i].x) > 0) {
	    cv::line(rgbFrames, points1[i], points2[i], cv::Scalar(0, 0, 255), 1, 1, 0);	       
	    cv::circle(rgbFrames, points1[i], 2, cv::Scalar(255, 0, 0), 1, 1, 0);
	    cv::line(opticalFlow, points1[i], points2[i], cv::Scalar(0, 0, 255),  1, 1, 0);
	    circle(opticalFlow, points1[i], 1, cv::Scalar(255, 0, 0), 1, 1, 0);
	  } else {
	    cv::line(rgbFrames, points1[i], points2[i], cv::Scalar(0, 255, 0), 1, 1, 0);
	    cv::circle(rgbFrames, points1[i], 2, cv::Scalar(255, 0, 0), 1, 1, 0);
	    cv::line(opticalFlow, points1[i], points2[i], cv::Scalar(0, 255, 0), 1, 1, 0);
	    cv::circle(opticalFlow, points1[i], 1, cv::Scalar(255, 0, 0), 1, 1,  0);
	  }
	  points1[k++] = points1[i];
	  
	}
	
	cv::goodFeaturesToTrack(grayFrames, points1, MAX_COUNT, 0.01, 10, cv::Mat(), 3, 0, 0.04);
	
      }
      
      cv::imshow(rawWindow, rgbFrames);
      cv::imshow(opticalFlowWindow, opticalFlow);
      
      std::swap(points2, points1);
      points1.clear();
      grayFrames.copyTo(prevGrayFrame);
      
      keyPressed = cv::waitKey(10);
      if (keyPressed == 27) {
	break;
      } else if (keyPressed == 'r') {
	opticalFlow = opticalFlow = cv::Mat(48,84, CV_32FC3);///RE OJO!!!
      }
      
    }
}
