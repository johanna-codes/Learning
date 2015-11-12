#include <iostream>
#include <armadillo>
//#include <hdf5.h>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
  {
  mat A = randu<mat>(100,100);
  
  //cout << A << endl;
  
  A.save("A.h5", hdf5_binary);
  A.save("A.dat", raw_ascii);
  
  //mat B;

  //B.load("A.h5", hdf5_binary);
  //cout << B << endl;
  
  //To read in Matlab
  //hinfo = hdf5info('A.h5');
  //dset = hdf5read(hinfo.GroupHierarchy.Datasets(1));
  
  
  //To save in Matlab with name myfile.h5, the matrix generated with uint8(magic(5))
  //hdf5write('myfile.h5', '/dataset1', uint8(magic(5)));
  
  
  return 0;
  }