#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(int argc, char** argv)
  {
  
    // create synthetic data with 2 Gaussians

uword N = 10000;
uword d = 5;

mat data(d, N, fill::zeros);

vec mean0 = linspace<vec>(1,d,d);
vec mean1 = mean0 + 2;

uword i = 0;

while(i < N)
  {
  if(i < N)  { data.col(i) = mean0 + randn<vec>(d); ++i; }
  if(i < N)  { data.col(i) = mean0 + randn<vec>(d); ++i; }
  if(i < N)  { data.col(i) = mean1 + randn<vec>(d); ++i; }
  }


gmm_diag model;

model.learn(data, 2, maha_dist, random_subset, 10, 5, 1e-10, true);

model.means.print("means:");

double  scalar_likelihood = model.log_p( data.col(0)    );
rowvec     set_likelihood = model.log_p( data.cols(0,9) );

double overall_likelihood = model.avg_log_p(data);

uword   gaus_id  = model.assign( data.col(0),    eucl_dist );
urowvec gaus_ids = model.assign( data.cols(0,9), prob_dist );

urowvec hist1 = model.raw_hist (data, prob_dist);
 rowvec hist2 = model.norm_hist(data, eucl_dist);

model.save("my_model.gmm");
    
    
  
  return 0;
  }
