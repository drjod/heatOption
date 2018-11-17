

#include "stru_matrix.h"

using namespace stru;
#include "matrixIO.h"
#include "matrix_math.h"
#include "gauss.h"
#include "bcgs.h"
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
	for(int i=0; i<1000;++i)
		v2 = m * v1;
}

BENCHMARK(matrixMatrixMultiplication)
{
	DMat m(DIM, DIM), m2(DIM, DIM);
	m2 = m * m2;
}


BENCHMARK(scaleAndAddVectors)
{
	DVec v1(DIM), v2(DIM), v3(DIM);
	for(int i=0; i<100000;++i)
		v3 = scale_and_add(v1, 3., v2);
}


BENCHMARK(matrixDoubleMultiplication)
{
	DMat m(DIM, DIM);
	for(int i=0; i<1000;++i)
		m *= 1000.;
}

BENCHMARK(functionOnMatrices)
{
	DMat m(DIM, DIM), m2(DIM, DIM);
	m.apply(m2, Mul_assign<double>());
}


BENCHMARK(vectorAddition)
{
	DVec v1(DIM), v2(DIM), v3(DIM);
	for(int i=0; i<1000;++i)
		v3 = v1 + v2;
}


BENCHMARK(matrixMultiplication)
{
	DMat m1(DIM, DIM), m2(DIM, DIM), m3(DIM, DIM);
	//for(int i=0; i<1000;++i)
		m3 = m1 * m2;
}


BENCHMARK(doubleMatrixMultiplication)
{
	DMat m1(DIM, DIM), m2(DIM, DIM), m3(DIM, DIM), m4(DIM, DIM);
	m4 = m1 * m2 * m3;
}


BENCHMARK(gauss)
{
	/*DMat A{{2., 1., -1.},{-3., -1., 2.},{-2., 1., 2.}};
    DVec b{8., -11., -3.};
    DVec x(3);
	*/
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


// --------------------------------------------------------
// parallel


BENCHMARK(gauss_large)
{
	const int size = 5000;

	DMat A(size, size);
    DVec b(size), x(size);

    for(int i=1; i<size-1;++i)
    {
        A(i, i+1) = 1;
        A(i, i) = -2;
        A(i, i-1) = 1;
    }
    A(0, 0) = 1;
    A(size-1, size-1) = 1;
    b(0) = 2;
    b(size-1) = 1;

	classical_elimination(A, b);
	x = back_substitution(A, b);
	//std::cout << x << '\n';
}


BENCHMARK(parallelMatrixVectorMultiplication)
{
	const int size = 10000;
	const int size2 = 100000;
	DMat* m = new DMat(size, size2);
	DVec* v1 = new DVec(size2);
	DVec v2(size);
	//for(int i=0; i<1000;++i)
		v2 = matrix_multiply(*m, *v1);

	delete m;
	delete v1;
}

