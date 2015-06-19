#include <stdio.h>
#include "omp.h"


static long num_steps = 100000;
double step;

#define NUM_THREADS 4


int main(int argc, char** argv)
{
  printf(" My solution 1 \n");
  int i, j; 
  double pi;
  
  double sum [NUM_THREADS];
  
  for (j=0;j< NUM_THREADS; j++){
    sum [j] = 0.0;
  }
  
  step = 1.0/(double) num_steps;
  
  double x [ num_steps];
  
  #pragma omp parallel
  {
    #pragma omp for
    for (i=0;i< num_steps; i++){    
    int ID = omp_get_thread_num();
    
    x[i] = (i+0.5)*step;
    sum [ID] += 4.0/(1.0+x[i]*x[i]);
    
  }
  }
  
  double total_sum = 0.0;
  for (j=0;j< NUM_THREADS; j++){
    total_sum  += sum [j];
  }
  
  pi = step * total_sum;
  
  printf(" Done %4.10f \n ", pi);
  return 0;
  
}


