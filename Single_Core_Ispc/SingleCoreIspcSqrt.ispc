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


export void ispc_sqrt(uniform double vin[], uniform double vout[],
                   uniform int count) {
    foreach (index = 0 ... count) {
        vout[index] = smartSqrt(vin[index]);
    }
}




