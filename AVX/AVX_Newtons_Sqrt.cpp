#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <immintrin.h>
#include <iostream>



__m256 square_root_AVX(__m256 num_AVX) {
	__m256 x1_AVX = _mm256_mul_ps(num_AVX, _mm256_set1_ps(1.0f));
    x1_AVX = _mm256_div_ps(x1_AVX, _mm256_set1_ps(2.0f));
  
    //float x2= (x1 + (num / x1)) / 2;
    __m256 x2_AVX  = _mm256_div_ps(num_AVX, x1_AVX);
    x2_AVX  = _mm256_add_ps(x1_AVX, x2_AVX);
    x2_AVX  = _mm256_div_ps(x2_AVX, _mm256_set1_ps(2.0f));
  
    //while(fabs(x1 - x2) >= 0.0001) {
	while(true){
	//following logic gets the absolute value of (x1_AVX - x2_AVX)
	__m256  diff_AVX       = _mm256_sub_ps(x1_AVX,x2_AVX);
	__m256  one_AVX  = _mm256_xor_ps(_mm256_set1_ps(-1.0f),_mm256_set1_ps(1.0f)); 
	__m256  cmp_result=_mm256_cmp_ps ( diff_AVX,_mm256_set1_ps(0.0f), _CMP_LT_OS);
	__m256  b = _mm256_and_ps ( cmp_result,one_AVX);
	__m256  result = _mm256_xor_ps (b, diff_AVX);
	
	//logic to check the break conditions
	__m256 vcmp = _mm256_cmp_ps(result, _mm256_set1_ps(0.0001), _CMP_GE_OS);
	int mask = _mm256_movemask_ps(vcmp);
    if(mask == 0x00)
		break;
    
    //x1 = x2;
    x1_AVX=x2_AVX;
    
    //x2 = (x1 + (num / x1)) / 2;
    x2_AVX  = _mm256_div_ps(num_AVX, x1_AVX);
    x2_AVX  = _mm256_add_ps(x1_AVX, x2_AVX);
    x2_AVX  = _mm256_div_ps(x2_AVX, _mm256_set1_ps(2.0f));
  }
  return x2_AVX;
}


int main(int argc, char *argv[])
{
	 __m256 rInput_AVX, rOutput_AVX; // variables for AVX
	float *randNums, *sqrtResults;   // data pointers
	float *pInput,*pOutput;         // work pointer
	int NUM_ELEMENTS=15000000;
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
    rOutput_AVX  = square_root_AVX(rInput_AVX);

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
