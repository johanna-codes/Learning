//Taken from: http://docs.opencv.org/doc/tutorials/ml/introduction_to_svm/introduction_to_svm.html
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

using namespace cv;


int main()
{
   
  
   Mat img, image_tr;
   img = imread("dolphins.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
   
 
   cv::Mat imgTranslated(img.size(),img.type(),cv::Scalar::all(0));
   img(cv::Rect(50,30,img.cols-50,img.rows-30)).copyTo(imgTranslated(cv::Rect(0,0,img.cols-50,img.rows-30)));


   
    imshow("Original Image", img); // show it to the user
    imshow("Translated Image", imgTranslated); // show it to the user

    waitKey(0);

}


