http://stackoverflow.com/questions/8915833/opencv-distance-transform-outputting-an-image-that-looks-exactly-like-the-input
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <armadillo>
#include <iomanip>
#include <vector>

using namespace std;
using namespace arma;

inline mat openCVtoArma( cv::Mat opencvMat );
inline cv::Mat ArmatoOpenCV(mat armaMat);



int main( int argc, const char** argv )
{
  
  cv::Mat original;
  original = cv::imread("templ.png", 0);
  cv::Mat binary = original>= 128;
  
  cv::Mat distT;
  cv::distanceTransform(binary, distT, CV_DIST_L2, 5);
  
  
  
  cv::imshow("original", original);
  cv::imshow("non-normalized", distT);
  
  cv::normalize(distT, distT, 0.0, 1.0, cv::NORM_MINMAX);
  cv::Mat colour;
  cv::cvtColor(distT, colour, CV_GRAY2BGR);

  cv::imshow("normalized", distT);
  cv::imshow("colour", colour);
  cv::waitKey();
  
  
  
  
  
  
  
  
}




/*
 * cmake_minimum_required(VERSION 2.8)
 * project(weizmann)
 * #set(CMAKE_BUILD_TYPE Release)
 * find_package( OpenCV REQUIRED)
 * find_package( Armadillo REQUIRED)
 * set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -pedantic -fopenmp")
 * add_executable( my_run_dist_T.exe my_distTransform.cpp)
 * target_link_libraries( my_run_dist_T.exe ${OpenCV_LIBS} -larmadillo)
 */

