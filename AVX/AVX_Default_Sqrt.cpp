#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <immintrin.h>
#include <iostream>

double square_root(int num) {
  double x1 = (num * 1.0) / 2;
  double x2= (x1 + (num / x1)) / 2;
  while(abs(x1 - x2) >= 0.0000001) {
    x1 = x2;
    x2 = (x1 + (num / x1)) / 2;
  }
  return x2;
}


int main(int argc, char *argv[])
{
	 __m256 rInput_AVX, rOutput_AVX; // variables for AVX
	float *randNums, *sqrtResults;   // data pointers
	float *pInput,*pOutput;         // work pointer
	int NUM_ELEMENTS=60000000;
	// allocating memory 
	randNums = (float*) _mm_malloc (NUM_ELEMENTS*sizeof(float),32);
	sqrtResults = (float*) _mm_malloc (NUM_ELEMENTS*sizeof(float),32);


	struct timeval startwtime, endwtime;
	double seq_time;
	srand((unsigned int)time(NULL));
    float a = 5.0;
   
    printf("Input\n");
    for (int i=0;i<NUM_ELEMENTS;i++){
		randNums[i]=((float)rand()/(float)(RAND_MAX)) * a ;
		sqrtResults[i]=0.0f;
	}
	
	
	printf("0) %f\n", randNums[362538]);  //Checking result for any random input
	printf("0) %f\n", randNums[5387653]); 
	printf("Output\n");
	
	pInput = randNums; 
	pOutput = sqrtResults;
	
	gettimeofday (&startwtime, NULL);

	
	for (int i=0; i<NUM_ELEMENTS; i+=8){
    rInput_AVX   = _mm256_load_ps(pInput);
    rOutput_AVX  = _mm256_rsqrt_ps(rInput_AVX);

    _mm256_store_ps(pOutput,rOutput_AVX);
    pInput += 8;
    pOutput += 8;
    }
	
	gettimeofday (&endwtime, NULL);
	printf("0) %f\n",sqrtResults[362538]);   //Checking result for that random input
	printf("0) %f\n",sqrtResults[5387653]); 
	seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
		      + endwtime.tv_sec - startwtime.tv_sec);
	printf("Time taken in Secs = %f\n", seq_time);
    return 0;
}
