#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
  {
  mat A = randu<mat>(15,10000);
  mat cov_A = cov(A.t());
  cov_A.print("cov_A");
  vec std_A = stddev(A, 0, 1 );
  vec mean_A = mean(A, 1 );
  
  //A.print("A:");
  //std_A.print("std_A");
  //mean_A.print("mean_A");
  
  //mat mean_mat = mean_A%ones(4,10);
  //mat norm_A = A - mean_A%ones(4,10);
  
  
  return 0;
  }