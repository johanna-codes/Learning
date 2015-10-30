clear all
clc
orig_data = load('orig_data.dat');
W_cpp = load('pca_matrix.dat');
new_data_cpp = load('after_pca_data.dat');
new_data_cpp = new_data_cpp';



orig_data = orig_data';
[n_vec dim] = size(orig_data);
NP = floor(dim/2);


Sigma=cov(orig_data);
[U,S,V] = svd(Sigma);
W_matlab = U(:,1:NP);
new_data_matlab=orig_data*W_matlab;