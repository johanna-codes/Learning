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
mat bw;
bw.zeros(200,200);
// bw(1,1) = 255; 
// bw(3,3) = 255;


bw(49,49)  = 255;
bw(49,149) = 255;
bw(149,99) = 255;

//cout << bw << endl;

    /*bw <<  0  <<   0  <<   0  <<   0   <<  0  << endr
       <<  0  <<   1  <<   0  <<   0   <<  0  << endr
       <<  0  <<   0  <<   0  <<   0   <<  0  << endr
       <<  0  <<   0  <<   0  <<   1   <<  0  << endr
       <<  0  <<   0  <<   0  <<   0   <<  0  << endr;
       */

  

cv::Mat bxCV1,bxCV2;

bxCV1 = ArmatoOpenCV(bw);
bxCV1.convertTo(bxCV2, CV_8UC1);   

//cout << "bxCV1" << endl;
//cout << bxCV1 << endl;

//cout << "bxCV2" << endl;
//cout << bxCV2 << endl;

cv::Mat transfCV;
cv::distanceTransform(bxCV2, transfCV, CV_DIST_C, 5);
cv::imshow("Euclidean Transform1", transfCV);

//cout << transfCV << endl;

///Plot Euclidean Transform
	 transfCV *= 5000;
        pow(transfCV, 0.5, transfCV);

        cv::Mat dist32s, dist8u1, dist8u2, dist8u;

        transfCV.convertTo(dist32s, CV_32S, 1, 0.5);
        dist32s &= cv::Scalar::all(255);

        dist32s.convertTo(dist8u1, CV_8U, 1, 0);
        dist32s *= -1;

        dist32s += cv::Scalar::all(255);
        dist32s.convertTo(dist8u2, CV_8U);

        cv::Mat planes[] = {dist8u1, dist8u2, dist8u2};
        cv::merge(planes, 3, dist8u);
	cv::Mat greyMat;
	cv::cvtColor(dist8u, greyMat, CV_BGR2GRAY);
	cv::imshow("Original", bxCV2);
	cv::imshow("Euclidean Transform", greyMat);
	cv::imshow("dist8u", dist8u);
	cv::waitKey();
	//cv::imshow("Euclidean Training", transfCV);
	
///end Euclidean Transform



       
}



inline
mat
openCVtoArma(cv::Mat opencvMat)
{
  int rows = opencvMat.rows;
  int cols = opencvMat.cols;
  cv::Mat matT(opencvMat.t());
  
  fmat armaConv(matT.ptr<float>(),rows, cols);
  
  mat armaMat = conv_to< mat >::from( armaConv );
  
  //cout << opencvMat << endl << endl;
  
  //cout << setprecision(2) << fixed << armaMat << endl;
  
 
  return armaMat;
}



inline
cv::Mat
ArmatoOpenCV(mat armaMat)
{
  //armaMat.print("armaMat");

  int rows = armaMat.n_rows;
  int cols = armaMat.n_cols;
  
  fmat armaMat_f = conv_to< fmat >::from( armaMat );
  
  
  cv::Mat opencvMatTmp(cols, rows, CV_32FC1, armaMat_f.memptr());
  cv::Mat opencvMat(opencvMatTmp.t());
 //std::cout << "opencvMat: " << std::endl << opencvMat << std::endl;
 
  return opencvMat;
}





