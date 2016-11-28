#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "SingleCoreIspcSqrt.ispc.h"


int main(int argc, char *argv[])
{
	struct timeval startwtime, endwtime;
	double single_core_time;
    srand((unsigned int)time(NULL));
	int NUM_ELEMENTS=15000000;
	
    double a = 5.0;
    
    double randNums[NUM_ELEMENTS];
    
    double sqrtResults[NUM_ELEMENTS];
    
    printf("\nInput\n");
    
    for (int i=0;i<NUM_ELEMENTS;i++){
		randNums[i]=(((double)rand()/(double)(RAND_MAX)) * a );
		//printf("%d) %f\n",i, randNums[i]);
	}
	
	printf("0) %f\n", randNums[0]);
	gettimeofday (&startwtime, NULL);
	ispc::ispc_sqrt(randNums,sqrtResults,NUM_ELEMENTS);
	gettimeofday (&endwtime, NULL);
	
	printf("Output\n");
	//for (int i=0;i<NUM_ELEMENTS;i++){
		//sqrtResults[i]=smartSqrt(randNums[i]) ;
		printf("0) %f\n",sqrtResults[0]);
	//}
	single_core_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
		      + endwtime.tv_sec - startwtime.tv_sec);
	printf("Time taken in Secs = %f\n", single_core_time);
	
    return 0;
}
