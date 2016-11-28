#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "MultipleCoreIspcSqrt.ispc.h"


int main(int argc, char *argv[])
{
    struct timeval startwtime, endwtime;
	double multi_core_time;
    srand((unsigned int)time(NULL));
	int NUM_ELEMENTS=15000000;
	int NUM_TASKS = 15;
	
	if ( argc == 2 ) {
    NUM_TASKS = atoi( argv[1] );
	}
	
	printf("NUM_TASKS: %d\n",NUM_TASKS);
	int BLOCK_SIZE = NUM_ELEMENTS/NUM_TASKS;
	
    double a = 5.0;
    
    double randNums[NUM_ELEMENTS];
    
    double sqrtResults[NUM_ELEMENTS];
    
    printf("\nInput\n");
    
    for (int i=0;i<NUM_ELEMENTS;i++){
		randNums[i]=(((double)rand()/(double)(RAND_MAX)) * a );
		//printf("%d) %f\n",i, randNums[i]);
	}
	
	printf("0) %f\n", randNums[2651489]);  //Checking result for any one random input
	
	gettimeofday (&startwtime, NULL);
	ispc::ispc_sqrt_task(randNums,sqrtResults,BLOCK_SIZE,NUM_ELEMENTS,NUM_TASKS);
	gettimeofday (&endwtime, NULL);
	
	printf("Output\n");
	//for (int i=0;i<NUM_ELEMENTS;i++){
		//sqrtResults[i]=smartSqrt(randNums[i]) ;
		printf("0) %f\n",sqrtResults[2651489]);   //Checking result for that one random input
	//}
	multi_core_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
		      + endwtime.tv_sec - startwtime.tv_sec);
	printf("Time taken in Secs = %f\n", multi_core_time);
    return 0;
}
