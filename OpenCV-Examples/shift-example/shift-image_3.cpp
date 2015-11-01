#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

using namespace cv;

Mat Shift_Image( Mat src_in, int num_pixels_x, int num_pixels_y);


int main()
{
  
  
  Mat img, image_tr;
  img = imread("puppy.bmp", CV_LOAD_IMAGE_COLOR);   // Read the file
  
  
  cv::Mat imgTranslated_right, imgTranslated_left;
  
  imgTranslated_right = Shift_Image(img, 30, 30);
  imgTranslated_left  = Shift_Image(img, -30, -30);
  
  
  
  imshow("Original Image", img); // show it to the user
  imshow("Translated Image Left", imgTranslated_left); // show it to the user
  imshow("Translated Image Right", imgTranslated_right); // show it to the user
  
  waitKey(0);
  
}

Mat 
Shift_Image( Mat src_in, int num_pixels_x, int num_pixels_y)
{
  
  
  Mat img_out;
  
  
  Mat rot_mat = (Mat_<double>(2,3) << 1, 0, num_pixels_x, 0, 1, num_pixels_y);
  warpAffine( src_in, img_out, rot_mat, src_in.size() );
  
  if (num_pixels_x>0) //Move right
  {   
    
    Mat col = src_in.col(0);
    Mat row = src_in.row(0);
    
    
    for (int i=0; i<abs(num_pixels_x); ++i)
    {
      col.col(0).copyTo(img_out.col(i));
      
    }
    
    for (int i=0; i<abs(num_pixels_y); ++i)
    {
      row.row(0).copyTo(img_out.row(i));
      //src_in.copyTo(img_out,crop);
    }
  }
  
  if (num_pixels_x<0) //Move right
  {   
    
    int w = src_in.size().width;
    int h = src_in.size().height;
    Mat col = src_in.col(w-1);
    Mat row = src_in.row(h-1);
    
    for (int i=w-abs(num_pixels_x) ; i<w; ++i)
    {
      col.col(0).copyTo(img_out.col(i));
      //row.row(0).copyTo(img_out.row(i));
    } 
    
    for (int i=h-abs(num_pixels_y) ; i<h; ++i)
    {
      //col.col(0).copyTo(img_out.col(i));
      row.row(0).copyTo(img_out.row(i));
    }
  }
  
  
  
  
  
  
  
  
  std::cout << src_in.size().width << " & " <<  src_in.size().height << std::endl;
  std::cout << img_out.size().width << " & " <<  img_out.size().height << std::endl;
  return img_out;
}
