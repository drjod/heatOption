#ifndef DOUBLE_SWEEP_H
#define DOUBLE_SWEEP_H


DVec double_sweep(DVec a, DVec b, DVec c, DVec f)
{
	long N =  a.size()-1;

	DVec L(N);
    L[0] = 0.0; 

    for (long i =1; i < N; ++i)
		L[i] = ( -c[i] ) / ( b[i] + ( a[i] * L[i-1] ) );

    DVec K(N);
    K[0] = f[0];  // left BC

    for (long i=1; i < N; ++i)
        K[i] = ( f[i] - ( a[i] * K[i-1] ) ) / ( b[i] + ( a[i] * L[i-1] ) );


    DVec U(N+1); // result vector
    U[0] = f[0];
    U[N] = f[N];

    for(long i = N - 1; i >= 1; --i)
        U[i] = ( L[i] * U[i + 1] ) + K[i];

	return U;
}

#endif


