#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <armadillo>
#include <iomanip>
#include <vector>

using namespace std;
using namespace arma;



int
main(int argc, char** argv)
{

  
  // armadillo to mat
arma::fmat arma2matData = arma::randu<arma::fmat>(14, 100);
//std::cout << "arma2matData: " << std::endl << arma2matData << std::endl;
     
cv::Mat cvMatConvTmp(100, 14, CV_32FC1, arma2matData.memptr());
cv::Mat cvMatConv(cvMatConvTmp.t());

//std::cout << "cvMatConv: " << std::endl << cvMatConv << std::endl;


cout << arma2matData.col(85) << endl;
cout << cvMatConvTmp.row(85) << endl;
cout << cvMatConv.col(85) << endl;
  
  

  
  
  return 0;
  
}




