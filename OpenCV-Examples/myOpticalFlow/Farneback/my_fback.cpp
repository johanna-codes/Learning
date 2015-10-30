#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

static void help()
{
    cout <<
            "\nThis program demonstrates dense optical flow algorithm by Gunnar Farneback\n"
            "Mainly the function: calcOpticalFlowFarneback()\n"
            "Call:\n"
            "./fback\n"
            "This reads from video camera 0\n" << endl;
}
static void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step,
                    double, const Scalar& color)
{
    for(int y = 0; y < cflowmap.rows; y += step)
        for(int x = 0; x < cflowmap.cols; x += step)
        {
            const Point2f& fxy = flow.at<Point2f>(y, x);
            line(cflowmap, Point(x,y), Point(cvRound(x+fxy.x), cvRound(y+fxy.y)),
                 Scalar(0, 0, 255));
            circle(cflowmap, Point(x,y), 1, color, -1);
        }
}

int main(int, char**)
{
  
   
    VideoCapture cap("daria_multiactions.avi");
    double frmcount = cap.get(CV_CAP_PROP_FRAME_COUNT);
    double pi = M_PI;
    //cout << pi << endl;

    //help();
    if( !cap.isOpened() )
        return -1;

    Mat prevgray, gray, flow, cflow, frame;
    //namedWindow("flow", 1);
    

     for(int fr=0; fr<frmcount; fr++)
    {
        cap >> frame;
	Mat hsv(frame.size(), CV_32FC3, cvScalar(0,0,0));
	cvtColor(frame, gray, COLOR_BGR2GRAY);

        if( prevgray.data )
        {
            calcOpticalFlowFarneback(prevgray, gray, flow, 0.5, 3, 5, 3, 5, 1.2, 0);
            //cvtColor(prevgray, cflow, COLOR_GRAY2BGR);
            //drawOptFlowMap(flow, cflow, 10, 0.5, Scalar(0, 255, 0));
	    
	    
	    Mat flow_xy[2];
	    Mat hsv_channels[3];
	    Mat mag, ang;
	    
	    split(flow, flow_xy);
	    split(hsv,hsv_channels);
    
	    cartToPolar(flow_xy[0], flow_xy[1], mag, ang, true);
	    double mag_max, mag_min;
	    cv::minMaxLoc(mag, &mag_min, &mag_max);
	    mag.convertTo(mag, -1, 1.0/mag_max);
	    
	    hsv_channels[0] = ang;
	    hsv_channels[1].setTo(Scalar(255)) ;
	    hsv_channels[2] = mag;
	
	    merge(hsv_channels, 3, hsv);
	    cvtColor(hsv, cflow, COLOR_HSV2BGR);
	    
	    
	    //cvtColor(mag, cflow, COLOR_GRAY2BGR);
	    //cout << mag.channels() << endl;
	    //cout << mag.depth() << endl;
	    
	   
	    
	    for (int x = 0 ; x < frame.cols ; ++x ){
	      for (int y = 0 ; y < frame.rows ; ++y ) {
		if  (mag.at<float>(y,x) > 0.4)
		{
		  //cout << mag.at<float>(y,x) << " ";
		  frame.at<cv::Vec3b>(y,x)[0] = 0;
		  frame.at<cv::Vec3b>(y,x)[1] = 0;
		  frame.at<cv::Vec3b>(y,x)[2] = 255;
		  
		//imshow("orig", frame);
		//waitKey();
		  
		}
		
	      }
	      
	    }

            
///http://docs.opencv.org/trunk/doc/py_tutorials/py_video/py_lucas_kanade/py_lucas_kanade.html	    
//http://stackoverflow.com/questions/7693561/opencv-displaying-a-2-channel-image-optical-flow
///See openCV samples: gpu/performance/farneback_optical_flow.cpp


imshow("orig", frame);
imshow("flow", cflow);
//imshow("ang",ang);    
//imshow("mag",mag); 
//waitKey();
	  
	}
        if(waitKey(30)>=0)
            break;
        std::swap(prevgray, gray);
    }
    return 0;
}
