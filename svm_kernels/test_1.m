%%Euclidean Space
clear all
addpath('/media/johanna/HD1T/Toolbox/libsvm-3.20/matlab');
X_train = randn(10,100);
gt_train = sign(randn(1,100));

X_test = randn(10,50);
gt_test = sign(randn(1,50));
 
LINEAR_KERNEL = @(X,Y) X' * Y;
RBF_KERNEL = @(X,Y) exp(-(16* sum((X - Y) .^ 2)));

K_train = compute_kernel_svm_2(X_train,X_train,LINEAR_KERNEL);
K_test = compute_kernel_svm_2(X_test,X_train,LINEAR_KERNEL);

model = svmtrain(gt_train', [[1:size(K_train,1)]' K_train], '-t 4 -q ');
svmpredict(gt_test',[[1:size(K_test,1)]' K_test], model);

K_train = compute_kernel_svm_2(X_train,X_train,RBF_KERNEL);
K_test = compute_kernel_svm_2(X_test,X_train,RBF_KERNEL);

model = svmtrain(gt_train', [[1:size(K_train,1)]' K_train], '-t 4 -q -c 0.001');
[predict_label, accuracy, dec_values] = svmpredict(gt_test',[[1:size(K_test,1)]' K_test], model);

