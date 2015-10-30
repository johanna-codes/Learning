#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
  {
  mat A = randu<mat>(100000,20);
  mat B = randu<mat>(100000,20);
  //double nor;
  double Kp1, Kp2;
  double n_secs1, n_secs2;
  mat C;
  wall_clock timer1;
  wall_clock timer2;
  
  timer1.tic();
  C = A.t()*B;
  //nor = norm(C,"fro");
  Kp1 = pow( norm(C,"fro"), 2);
  n_secs1 = timer1.toc();
  cout << "1 took " << n_secs1 << " seconds" << endl;
  
  timer2.tic();

  Kp2 = trace(A.t()*B*B.t()*A);
  n_secs2 = timer2.toc();
  cout << "2 took " << n_secs2 << " seconds" << endl;

  
  
  
  cout  << Kp1 << " should be equal to " << Kp2 << endl;
  mat X;
  X << 1 << 2 << 3 << endr
    << 4 << 5 << 6 << endr
    << 7 << 8 << 9 << endr;
    
     mat Y;
  Y << 10 << 11 << 12 << endr
    << 13 << 14 << 15 << endr
    << 16 << 17 << 18 << endr;
  
  return 0;
  }