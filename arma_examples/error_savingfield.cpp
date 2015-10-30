#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
{
field<rowvec> loocv (25,2); 

loocv.print("Print works");
loocv.save("LOOCV_3actions.dat");
return 0;
}


  