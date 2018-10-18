

#include "stru3_matrix.h"

using namespace stru3;

#include "stru3_gauss.h"
#include "stru3_bcgs.h"
#include "diffusion.h"

#define DIM 1000


BENCHMARK(matrixAdditionSubtractionChain)
{
	DMat m(DIM, DIM);
	DMat m2(DIM, DIM);
	m2 = m + m - m + m - m + m + m - m + m + m;
}


BENCHMARK(matrixVectorMultiplication)
{
	DMat m(DIM, DIM);
	DVec v1(DIM), v2(DIM);
	for(int i=0; i<1000; ++i)
		v2 = m * v1;
}

//BENCHMARK(matrixMatrixMultiplication)
//{
//	DMat m(DIM, DIM), m2(DIM, DIM);
//	m2 = m * m2;
//}


BENCHMARK(scaleAndAddVectors)
{
	DVec v1(DIM), v2(DIM), v3(DIM);
	
	for(int i=0; i<100000; ++i)
		v3 = scale_and_add(v1, 3., v2);
}


BENCHMARK(scaleAndAddRows)
{
	DMat m1(DIM, DIM), m2(DIM, DIM), m3(DIM, DIM);
	Slice_iter<double> s1 = m1[10], s2 = m2[10], s3 = m3[10]; 
	
	for(int i=0; i<100000; ++i)
		s1 = scale_and_add(s2, 3., s3);
}

BENCHMARK(matrixDoubleMultiplication)
{
	DMat m(DIM, DIM);
	for(int i=0; i<1000;++i)
		m *= 1000.;
}

//BENCHMARK(functionOnMatrices)
//{
//	DMat m(DIM, DIM), m2(DIM, DIM);
//	m.apply(m2, Mul_assign<double>());
//}


BENCHMARK(vectorAddition)
{
	DVec v1(DIM), v2(DIM), v3(DIM);
	for(int i=0; i<1000;++i)
		v3 = v1 + v2;
}


//BENCHMARK(matrixMultiplication)
//{
//	DMat m1(DIM, DIM), m2(DIM, DIM), m3(DIM, DIM);
//	m3 = m1 * m2;
//}


//BENCHMARK(doubleMatrixMultiplication)
//{
//	DMat m1(DIM, DIM), m2(DIM, DIM), m3(DIM, DIM), m4(DIM, DIM);
//	m4 = m1 * m2 * m3;
//}


BENCHMARK(gauss)
{
	//DMat A{{2., 1., -1.},{-3., -1., 2.},{-2., 1., 2.}};
    //DVec b{8., -11., -3.};
    //DVec x(3);
	
	DMat A(3, 3);
	DVec b(3), x(3);
	for(int i=0; i<10000;++i)
	{
		A(0, 0) = 2., A(0, 1) = 1., A(0, 2) = -1.;
		A(1, 0) = -3., A(1, 1) = -1., A(1, 2) = 2.;
		A(2, 0) = -2., A(2, 1) = 1., A(2, 2) = 2.;
		b[0] = 8., b[1] = -11., b[2] = -3.;

		classical_elimination(A, b);
		x = back_substitution(A, b);
	}
}


BENCHMARK(bcgs)
{
	for(int i=0; i<3;++i)
	solve(DIM);	
}

