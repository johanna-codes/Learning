#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
  {
 
field<vec> person18(4);

person18(0) = randu<vec>(2);
person18(1) = randu<vec>(2);
person18(2) = randu<vec>(2);
person18(3) = randu<vec>(2);

person18.save("person18.txt");


  }