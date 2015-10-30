#include "opencv/cv.h"
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <stdio.h>

std::vector<cv::Point2f> corners;
std::vector<cv::Point2f> corners_b;
double qualityLevel = 0.01;
double minDistance = 10;
int blockSize = 3;
bool useHarrisDetector = false;
double k = 0.04;
int maxCorners = 400;
int maxTrackbar = 100;

void MotionDetection(cv::Mat frame1, cv::Mat frame2)
{
    cv::Mat prev, next;
    cvtColor(frame1, prev, CV_BGR2GRAY); 
    cvtColor(frame2, next, CV_BGR2GRAY); 
    goodFeaturesToTrack( prev, 
            corners,
            maxCorners,
            qualityLevel,
            minDistance,
            cv::Mat(),
            blockSize,
            useHarrisDetector,
            k );
    cornerSubPix(prev, 
            corners,
            cvSize( 10, 10 ) ,
            cvSize( -1, -1 ), 
            cvTermCriteria( CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03 ) );
    std::vector<uchar> features_found;
    features_found.reserve(maxCorners);
    std::vector<float> feature_errors;
    feature_errors.reserve(maxCorners);
    calcOpticalFlowPyrLK(prev, next, corners, corners_b, features_found, 
            feature_errors, cvSize( 10, 10 ), 5, cvTermCriteria( CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.3 ), 0);
    IplImage g = next;
    for( int i = 0; i < maxCorners; ++i )
    {
        CvPoint p0 = cvPoint( cvRound( corners[i].x ), cvRound( corners[i].y ) );
        CvPoint p1 = cvPoint( cvRound( corners_b[i].x ), cvRound( corners_b[i].y ) );
        cvLine( &g, p0, p1, CV_RGB(255,0,0), 3, CV_AA );
    }
    cv::Mat rs(&g);
    imshow( "result window", rs );  
    int key = cv::waitKey(5);
}

int main(int argc, char* argv[])
{
    cv::VideoCapture cap;
    if( argc == 2 )
	cap.open(argv[1]); 
     
    
    if(!cap.isOpened())              
    {
        std::cout<<"[!] Error: cant open camera!"<<std::endl;
        return -1;
    }
    cv::Mat edges;
    cv::namedWindow("result window", 1);
    cv::Mat frame, frame2;
    cap >> frame;
    while(1)
    {
        cap >> frame2;
        MotionDetection(frame, frame2);
    }
    
    cv::destroyAllWindows();
    return 0;
}