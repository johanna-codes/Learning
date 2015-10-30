#include <stdio.h>
#include <opencv2/opencv.hpp>
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
  
  mat training_data;
  training_data.load("training_data.dat");
  
  fvec labels;
  labels.load("labels.dat");
  //labels.t().print("labesl:");
  
  int num_vec = training_data.n_cols;
  int dim =  training_data.n_rows;
  
  
  cv::Mat cvMatTraining(num_vec, dim, CV_32FC1);
  
  
  float fl_labels[num_vec] ;
  
  
  
  cout << "cvMatTraining Rows: " << cvMatTraining.rows << ". Cols: " << cvMatTraining.cols << endl;
  //cout << "cvMatLabels Rows: " << cvMatLabels.rows << ". Cols: " << cvMatLabels.cols << endl;
  
  for (uword m=0; m<num_vec; ++m)
  {
    for (uword d=0; d<dim; ++d)
    {
      cvMatTraining.at<float>(m,d) = training_data(d,m); 
      //cout << " OpenCV: " << cvMatTraining.at<float>(m,d) << " - Arma: " <<training_data(d,m); 
    }
    
    fl_labels[m] = labels(m);
    
    //cout <<" OpenCVLabel: " <<  fl_labels[m] << " ArmaLabel: " << labels(m) << endl;
    
  }
  
  cv::Mat cvMatLabels(num_vec, 1, CV_32FC1,fl_labels );
  
  //cv::Mat MatLabels2(num_vec, 1, CV_32FC1, cvMatLabels);
  
  
  
  cout << "Setting parameters" << endl;
  CvSVMParams params;
  params.svm_type    = CvSVM::C_SVC;
  params.kernel_type = CvSVM::RBF; 
  params.gamma = 1;
  params.term_crit   = cvTermCriteria(CV_TERMCRIT_ITER,  (int)1e7, 1e-6);
  
  
  // Train the SVM
  cout << "Training" << endl;
  CvSVM SVM;
  //SVM.train_auto(cvMatTraining, cvMatLabels, cv::Mat(), cv::Mat(), params);
  //params = SVM.get_params();
  //cout << "parameters: done" << endl;
  
  
  SVM.train( cvMatTraining , cvMatLabels, cv::Mat(), cv::Mat(), params);
  cout << "End of Training" << endl;
  SVM.save("toysvm_multi_RBF");
  
  
  //CvSVM SVM;
  //SVM.load("toysvm_multi");
  
  
  int acc =0;
  for (uword i=0; i< labels.n_elem; ++i)
  {
    
    cv::Mat sampleMat =   cvMatTraining.row(i);
    //cv::Mat sampleMat = ( cv::Mat_<float>(1,2) << cvMatTraining.at<float>(i,0) , cvMatTraining.at<float>(i,1) );
    
    float response = SVM.predict(sampleMat, true);
    
    cout << "response " << response << endl;
    //cout << "Label is " << labels(i) <<" and it was classified as " << response << endl;
    if (labels(i)  ==  response )
    {
      acc++;
    }
    
  }
  
  cout << acc*100/num_vec << endl;
  
  
  
  
  
  
}
