#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>


using namespace cv;
using namespace std;


/// Global variables
Mat src, dst, tmp;

/**
 * @function main
 */
int main( int argc, char** argv )
{
  
  if(argc < 2 )
  {
    std::cout << "usage: " << argv[0] << " scale_factor " << endl;
    return -1;
    
  }
  
  
  float scale_factor = atof( argv[1] ); //COnvierte a INT. Cambiar
 
  /// Test image - Make sure it s divisible by 2^{n}
  src = imread( "lena.jpg" );
  if( !src.data )
    { printf(" No data! -- Exiting the program \n");
      return -1; }

  tmp = src;
  
  cout << "** Original Size " << tmp.cols << " & " << tmp.rows << endl;
  
  int n_cols =  int(tmp.cols*scale_factor);
  int n_rows =  int(tmp.rows*scale_factor);
	
	
  Mat scaled_image;
  
  
  if (scale_factor>1)
  {
    resize(tmp, dst, Size(n_cols, n_rows ), CV_INTER_CUBIC );
    cout << "** New Size " << dst.cols << " & " << dst.rows << endl;
    int mid_col_ori = tmp.cols/2;
    int mid_row_ori = tmp.rows/2;
    
    int mid_col_new = dst.cols/2;
    int mid_row_new = dst.rows/2;
    
    int rec_col = mid_col_new - mid_col_ori;
    int rec_row = mid_row_new - mid_row_ori;
    
    Rect roi(rec_col, rec_row, tmp.cols, tmp.rows);
    scaled_image = dst(roi);

    
  }
  else if (scale_factor==1)
  {
    scaled_image = tmp;
        
  }
  else
  {
    
    resize(tmp, dst, Size(n_cols, n_rows ) , CV_INTER_AREA);
    cout << "** New Size " << dst.cols << " & " << dst.rows << endl;
    
    int x = (tmp.cols - dst.cols)/2;
    int y = (tmp.rows - dst.rows)/2;
    
    //cout << x << " & " << y << endl;
    
    Mat black_border(tmp.size(),CV_8UC3, cv::Scalar(0,0,0)); // all white image
   
    dst.copyTo( black_border( Rect( x, y, dst.cols, dst.rows) )  );    
    scaled_image = black_border;
    
    
    
    //Adding Vertical Pixels
    //At the beginning
    cv::Mat col = tmp.col(0);

    for (int i=0; i<x ; ++i)
    {
      col.col(0).copyTo(scaled_image.col(i));
      
    }
    
    //At the end
    col = tmp.col(tmp.cols-1);
    for (int i=x+dst.cols; i<tmp.cols ; ++i)
    {
      col.col(0).copyTo(scaled_image.col(i));
      
    }
    
    //Adding horizontal pixels
    cv::Mat row = tmp.row(0);

    
     for (int i=0; i<y; ++i)
     {
       row.row(0).copyTo(scaled_image.row(i));
       //src_in.copyTo(img_out,crop);
     }
     
     row = tmp.row(tmp.rows-1);
     for (int i=y+dst.rows; i<tmp.rows; ++i)
     {
       row.row(0).copyTo(scaled_image.row(i));
       //src_in.copyTo(img_out,crop);
     }
    

    
  }


  
//   /// Create window
//   namedWindow( "Resized", CV_WINDOW_AUTOSIZE );
//   imshow(  "Resized", dst );
  
  namedWindow( "Original", CV_WINDOW_AUTOSIZE );
  imshow( "Original", src );
  
  
  namedWindow( "Cropped", CV_WINDOW_AUTOSIZE );
  imshow( "Cropped", scaled_image );
  
  waitKey();
  
  
  
  
  return 0;
}




// int main( int argc, char** argv )
// {
//   /// General instructions
//   printf( "\n Zoom In-Out demo  \n " );
//   printf( "------------------ \n" );
//   printf( " * [u] -> Zoom in  \n" );
//   printf( " * [d] -> Zoom out \n" );
//   printf( " * [ESC] -> Close program \n \n" );
// 
//   /// Test image - Make sure it s divisible by 2^{n}
//   src = imread( "lena.jpg" );
//   if( !src.data )
//     { printf(" No data! -- Exiting the program \n");
//       return -1; }
// 
//   tmp = src;
//   dst = tmp;
// 
//   /// Create window
//   namedWindow( window_name, CV_WINDOW_AUTOSIZE );
//   imshow( window_name, dst );
// 
//   /// Loop
//   while( true )
//   {
//     int c;
//     c = waitKey(10);
// 
//     if( (char)c == 27 )
//       { break; }
//     if( (char)c == 'u' )
//       { pyrUp( tmp, dst, Size( tmp.cols*2, tmp.rows*2 ) );
//         printf( "** Zoom In: Image x 2 \n" );
//       }
//     else if( (char)c == 'd' )
//      { pyrDown( tmp, dst, Size( tmp.cols/2, tmp.rows/2 ) );
//        printf( "** Zoom Out: Image / 2 \n" );
//      }
// 
//     imshow( window_name, dst );
//     tmp = dst;
//   }
//   return 0;
// }


