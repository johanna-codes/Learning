#include <stdio.h>
#include "omp.h"


static long num_steps = 100000;
double step;

#define NUM_THREADS 4


int main(int argc, char** argv)
{
  printf(" My solution 2 \n");
  int i;
  double pi;
  
  double sum;
  
  
  step = 1.0/(double) num_steps;
  
  double x [ num_steps];
  
  //#pragma omp parallel //Parece funcionar sin este. No estoy segura. Efectivamente no se necesita. Esta explicitamente incluido en #pragma
  {
    #pragma omp for //Sin este no funciona
    for (i=0;i< num_steps; i++){    
    
    x[i] = (i+0.5)*step;
    
    #pragma omp atomic //Sin este no funciona
    sum += 4.0/(1.0+x[i]*x[i]);
    
  }
  }
  
  
  pi = step * sum;
  
  printf(" Done %4.10f \n ", pi);
  return 0;
  
}


