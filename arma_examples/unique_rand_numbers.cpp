#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <armadillo>
#include <iomanip>

using namespace std;
using namespace arma;


int main()
{
  arma_rng::set_seed_random();

  uvec v1 = linspace<uvec>(0,99,100);
  uvec v2 = shuffle(v1);

  v2.t().print("v2:");


  return 0;
}
