%%Riemannian Manifolds

%http://www.nicta.com.au/wp-content/uploads/2015/02/JayasumanaHartleySalzmannLiHarandiCVPR13.pdf
%http://www.uq.id.au/a.wiliem/papers/harandi_wacv2012.pdf
%http://www.cv-foundation.org/openaccess/content_cvpr_2013/papers/Jayasumana_Kernel_Methods_on_2013_CVPR_paper.pdf

clear all
addpath('/media/johanna/HD1T/Toolbox/libsvm-3.20/matlab');

X_train = randn(10,10,100);
gt_train = sign(randn(1,100));

X_test = randn(10,10,50);
gt_test = sign(randn(1,50));

for i=1:100
    X_train(:,:,i)= X_train(:,:,i)*X_train(:,:,i)';
end

for i=1:50
    X_test(:,:,i)= X_test(:,:,i)*X_test(:,:,i)';
end




sigma = 1;
%%
RIEMANNIAN_KERNEL = @(X,Y,sigma) exp( -( dist_g(X,Y) )^2/(2*sigma^2) );


K_train = compute_kernel_svm(X_train,X_train, RIEMANNIAN_KERNEL, sigma);
K_test = compute_kernel_svm(X_test,X_train, RIEMANNIAN_KERNEL,sigma);


model = svmtrain(gt_train', [[1:size(K_train,1)]' K_train], '-t 4 -q ');
[predict_label, accuracy, dec_values] = svmpredict(gt_test',[[1:size(K_test,1)]' K_test], model);

