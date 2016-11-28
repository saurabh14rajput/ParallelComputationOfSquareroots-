#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


double smartSqrt(double x) {
    if (x <= 0)
        return 0;      
    int exp = 0;
    x = frexp(x, &exp); 
    if (exp & 1) {      
        exp--;
        x *= 2;
    }
    double y = (1+x)/2; // first approximation
    double z = 0;
     while (fabs((y-z) >= 0.0001)) {
        z = y;
        y = (y + x/y) / 2;
    }
    return ldexp(y, exp/2);
}



int main(int argc, char *argv[])
{
	struct timeval startwtime, endwtime;
	double seq_time;
    srand((unsigned int)time(NULL));
	int NUM_ELEMENTS=15000000;
    double a = 5.0;
    double randNums[NUM_ELEMENTS];
    double sqrtResults[NUM_ELEMENTS];
    printf("Input\n");
    for (int i=0;i<NUM_ELEMENTS;i++){
		randNums[i]=((double)rand()/(double)(RAND_MAX)) * a ;
		//printf("%d) %f\n",i, randNums[i]);
	}
	printf("0) %f\n", randNums[2651489]);  //Checking result for any one random input
	printf("Output\n");
	gettimeofday (&startwtime, NULL);
	for (int i=0;i<NUM_ELEMENTS;i++){
		sqrtResults[i]=smartSqrt(randNums[i]) ;
		//printf("%d) %f\n",i,sqrtResults[i]);
	}
	gettimeofday (&endwtime, NULL);
	printf("0) %f\n",sqrtResults[2651489]);   //Checking result for that one random input
	seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
		      + endwtime.tv_sec - startwtime.tv_sec);
printf("Time taken in Secs = %f\n", seq_time);
    return 0;
}
