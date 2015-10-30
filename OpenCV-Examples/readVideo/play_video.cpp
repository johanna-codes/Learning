//opencv3.0
#include "opencv2/opencv.hpp"
#include <iostream>
#include <iomanip>
using namespace cv;
using namespace std;
int main(int, char**)
{
    //VideoCapture cap(0); // open the default camera
    
    cv::VideoCapture cap("boxing.avi");

    if(!cap.isOpened())  // check if we succeeded
        return -1;

    namedWindow("VideoPlayer",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        
        
	    //****To print in frame Num of feature vectors ****
	    
	    double framerate = 25;
	    framerate= framerate/10; //calculate deciseconds
	    double time_frame = (cap.get(CV_CAP_PROP_POS_FRAMES)/2.5)/10;
	    std::stringstream num_frame;
	    
	    //set precision
	    double time_frame2 = ceil(time_frame*10)/10;
	    num_frame << time_frame2;
	    //num_frame << setprecision(3) << time_frame;
	    string text = num_frame.str();
	    int fontFace = cv::FONT_HERSHEY_SCRIPT_SIMPLEX;
	    
	    double fontScale = 1;
	    int thickness = 1;  
	    cv::Point textOrg(10, 100);
	    cv::putText(frame, text, textOrg, fontFace, fontScale, cv::Scalar::all(255), thickness,4);
	    //****end ****
	    
	    
        
        
        
        imshow("VideoPlayer", frame);
        if(waitKey(100) >= 0) break;
        
        //cvtColor(frame, edges, COLOR_BGR2GRAY);
        //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);
        //imshow("edges", edges);
        //if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
