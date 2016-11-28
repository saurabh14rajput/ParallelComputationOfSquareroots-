
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
    double precision=0.0001;
	double diff;
    //while (y != z)
     while (1) {    
        diff=abs(y-z);
        if(diff < precision)
			break;
        z = y;
        y = (y + x/y) / 2;
    }
    return ldexp(y, exp/2); // multiply answer by 2^(exp/2)
}

task void
ispc_sqrt_block(uniform double vin[], uniform double vout[],
                   uniform int block_size,uniform int num_elems){
    uniform int index_start = taskIndex * block_size;
    uniform int index_end = min((taskIndex+1) * block_size, (unsigned int)num_elems);

    foreach (yi = index_start ... index_end) {
        vout[yi] = smartSqrt(vin[yi]);
    }
}

export void
ispc_sqrt_task(uniform double vin[], uniform double vout[],
                   uniform int block_size,uniform int num_elems,uniform int num_tasks)
{

    launch[num_tasks] ispc_sqrt_block(vin, vout, block_size, num_elems) ;
}
