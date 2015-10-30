#include <stdio.h>
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

  int dim = 6;
  int n_vec = 100;
  mat uni_features( dim, n_vec );
  uni_features.randu();
  uni_features.save("orig_data.dat", raw_ascii);
  

  mat U;
  vec s;
  mat V;
  mat Sigma = cov( uni_features.t() );
  svd(U,s,V,Sigma);
  int dim_data = uni_features.n_rows;
  int n_vec_data = uni_features.n_cols;
  int NP = floor(dim_data/2); //Reduced by a 2 factor. //NO Reducing dimension. Only trasnforming the space
  mat trans_matrix_pca = U.cols( 0, NP-1 ); //Transformation Matrix
  
  mat tpr = uni_features.t()*trans_matrix_pca;

  uni_features = tpr.t();
  
  //cout << "U r&c "<<  U.n_rows << " & " << U.n_cols << endl;

  //cout << "Sigma r&c "<<  Sigma.n_rows << " & " << Sigma.n_cols << endl;
  
  //cout << "trans_matrix_pca r&c "<<  trans_matrix_pca.n_rows << " & " << trans_matrix_pca.n_cols << endl;
  //cout << "tpr r&c "<<  tpr.n_rows << " & " << tpr.n_cols << endl;
  //cout << "new uni_features r&c "<<  uni_features.n_rows << " & " << uni_features.n_cols << endl;
  
 
  
  
  trans_matrix_pca.save( "pca_matrix.dat", raw_ascii );
  uni_features.save("after_pca_data.dat", raw_ascii);
  

  
  
  

return 0;
}