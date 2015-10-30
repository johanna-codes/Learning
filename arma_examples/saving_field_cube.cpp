#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
  {
	field <cube> full_cov(3);

	cube x = randu<cube>(4,5,6);
	cube y = randu<cube>(4,5,6);
	cube z = randu<cube>(4,5,6);

full_cov(0) = x;
full_cov(1) = y;
full_cov(2) = z;

full_cov.save("field_cube");


  
  return 0;
  }
  
  
  
  


