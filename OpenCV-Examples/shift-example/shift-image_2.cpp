//Taken from: http://docs.opencv.org/doc/tutorials/ml/introduction_to_svm/introduction_to_svm.html
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

using namespace cv;

Mat Shift_Image( Mat src_in, int num_pixels);


int main()
{
  
  
  Mat img, image_tr;
  img = imread("dolphin.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file
  
  
  cv::Mat imgTranslated_right, imgTranslated_left;
  
  imgTranslated_right = Shift_Image(img, 10);
  //imgTranslated_left  = Shift_Image(img, -10);
  
  
  
  imshow("Original Image", img); // show it to the user
  //imshow("Translated Image Left", imgTranslated_left); // show it to the user
  imshow("Translated Image Right", imgTranslated_right); // show it to the user
  
  waitKey(0);
  
}

Mat 
Shift_Image( Mat src_in, int num_pixels)
{
  
  int num_p = abs(num_pixels);
  Size sz_src_in = src_in.size();
  Mat img_out(sz_src_in.height, sz_src_in.width, CV_8UC3);
  std::cout << img_out.size().width << " & " <<  img_out.size().height << std::endl;
  
  
  if (num_pixels>0) //Move right
  {
    Rect  roi;
    roi.x = 0;
    roi.y = 0;
    roi.width = sz_src_in.width-num_p;
    roi.height = sz_src_in.height-num_p;
    
    Mat crop;
    
    crop = src_in(roi);
    
    
    img_out =  Scalar::all(0);
    //src_in.copyTo( img_out );
    src_in.copyTo(img_out,crop);

    imshow("crop", crop); // show it to the user
    imshow("img_out", img_out); // show it to the user
     
    
    
  }
  
  if (num_pixels<0) //Move left
  {
    Rect  roi;
    roi.x = 0;
    roi.y = 0;
    roi.width = sz_src_in.width-num_p;
    roi.height = sz_src_in.height-num_p;
    
    Mat crop;
    
    crop = src_in(roi);
    
    //Mat col = crop.col(0);
    
    // Move the left boundary to the right
    img_out =  Scalar::all(0);
    crop.copyTo(img_out,img_out );
    
    
    
    
  }
  

  
  std::cout << src_in.size().width << " & " <<  src_in.size().height << std::endl;
  std::cout << img_out.size().width << " & " <<  img_out.size().height << std::endl;
  return img_out;
}
