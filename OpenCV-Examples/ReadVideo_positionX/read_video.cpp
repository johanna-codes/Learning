#include "opencv2/opencv.hpp"
#include <stdio.h>

using namespace std;

using namespace cv;

int main(int, char**)
{
  VideoCapture cap("bike.avi"); // open the default camera
  if(!cap.isOpened())  // check if we succeeded
        return -1;
  
  namedWindow("video",1);
  
  int num_frames = cap.get(CV_CAP_PROP_FRAME_COUNT);
  cout << "num_frames: " << num_frames << endl;
  
  
  for (int i=1; i<=3; i++)
  {
    cout << "i= " << i << endl;
    //VideoCapture cap2("bike.avi"); // open the default camera
    cap.set(CV_CAP_PROP_POS_FRAMES,i*30);
    int j=0;
    while(cap.get(CV_CAP_PROP_POS_FRAMES) < num_frames)
    {
      cout << " " << j++;
      Mat frame;
      
      cap >> frame; // get a new frame from camera
      
      imshow("video", frame);
      if(waitKey(30) >= 0) break;
    }
    cout << endl;
    
  }
  // the camera will be deinitialized automatically in VideoCapture destructor
  return 0;
}
//CV_CAP_PROP_POS_FRAMES

//C++: bool VideoCapture::set(int propId, double value)