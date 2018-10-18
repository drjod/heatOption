#include "stru_matrix.h"
using namespace stru;
#include "matrix_math.h"
#include "matrixIO.h"

double times2(const double& x)
{
	return 2 * x;
}

void _times2(double& x)
{
	x *= 2;
}

double multiply(const double& x, const double& y)
{
	return x * y;
}


TEST(struMatrix, constructNassign)
{
	// construct with extents
	DVec v3(3);
	v3 = 0.;
	EXPECT_EQ(v3.dim1(), 3);
	EXPECT_EQ(v3.size(), 3);
	testing::internal::CaptureStdout();
	std::cout << v3 << '\n';
    EXPECT_EQ("(0 0 0)\n", 
			testing::internal::GetCapturedStdout());
	
    DMat m23(2, 3);
	EXPECT_EQ(m23.dim1(), 2);
	EXPECT_EQ(m23.dim2(), 3);
	EXPECT_EQ(m23.size(), 6);

	DTen t234(2, 3, 4);
	EXPECT_EQ(t234.dim1(), 2);
	EXPECT_EQ(t234.dim2(), 3);
	EXPECT_EQ(t234.dim3(), 4);
	EXPECT_EQ(t234.size(), 24);

	// copy construct
	DMat m32(3, 2);
	m32 = 5.;
    DMat m32b = m32;

	testing::internal::CaptureStdout();
	std::cout << m32b << '\n';
    EXPECT_EQ("((5 5)(5 5)(5 5))\n", 
			testing::internal::GetCapturedStdout());

	// copy assign
    DMat m32c(3, 2); 
	m32c = m32;

	// xfer
	DMat m32d = xfer(m32b);
	m32d(1,1) = 10.;
	//
	testing::internal::CaptureStdout();
	std::cout << m32b << '\n';
	std::cout << m32d << '\n';
    EXPECT_EQ("((5 5)(5 10)(5 5))\n((5 5)(5 10)(5 5))\n", 
			testing::internal::GetCapturedStdout());

	DMat m32e(3, 2);
	m32e = 20.;
	DMat m32f = xfer(m32e);  // no copy of elements with constructor
	m32e = 30.;

	testing::internal::CaptureStdout();
	std::cout << m32e << '\n';
	std::cout << m32f << '\n';
    EXPECT_EQ("((30 30)(30 30)(30 30))\n((30 30)(30 30)(30 30))\n", 
			testing::internal::GetCapturedStdout());

	DMat m32h(3, 2);
	DMat m32g(3, 2);
	m32g = 20.;
	m32h = xfer(m32g);  // but copy of elements with assignment (otherwise scale_and_add with slides fails)
	//m32g = 30.;  // segmentation fault
	testing::internal::CaptureStdout();
	// std::cout << m32g << '\n';  // just smthng weird in there
	std::cout << m32h << '\n';
    EXPECT_EQ("((20 20)(20 20)(20 20))\n", 
			testing::internal::GetCapturedStdout());

	// construct from pointer (only 1D)
	double* p = new double[2];
	p[0] = 10.;
	p[1] = 11.;
	DVec v2(p, 2);
	testing::internal::CaptureStdout();
	std::cout << v2 << '\n';
    EXPECT_EQ("(10 11)\n", 
			testing::internal::GetCapturedStdout());

	// construct from array
	double a[3][2];
	DMat m32i(a);  // gets dims via template
    EXPECT_EQ(m32i.dim1(), 3); 
    EXPECT_EQ(m32i.dim2(), 2);

	// construct with unary function
	DMat m32j(m32h, times2);  // function returns value - double times2(const double&)
	testing::internal::CaptureStdout();
	std::cout << m32j << '\n';
    EXPECT_EQ("((40 40)(40 40)(40 40))\n", 
			testing::internal::GetCapturedStdout());

	// construct with binary function
	DMat m32k(m32h, multiply, 2.);  // function returns value - double multiply(const double&, const double&)
	testing::internal::CaptureStdout();
	std::cout << m32k << '\n';
    EXPECT_EQ("((40 40)(40 40)(40 40))\n", 
			testing::internal::GetCapturedStdout());

	// construct from row
	DMat m32l(3, 2); 
	m32l = 4.;
	m32l(1, 0) = 5.;
	Row<double, 1> r = m32l[1];
	DVec v2b = r;
	testing::internal::CaptureStdout();
	std::cout << v2b << '\n';
    EXPECT_EQ("(5 4)\n", 
			testing::internal::GetCapturedStdout());
}


TEST(struMatrix, indexing)
{
	DVec v(3);  // (1, 2, 3);
	v(0) = 1., v(1) = 2., v(2) = 3.;
	EXPECT_EQ(v(1), 2);
	EXPECT_EQ(v[1], 2);

	DMat m(3, 2);
	m(0, 0) = 1., m(0, 1) = 2., m(1, 0) = 3., m(1, 1) = 4., m(2, 0) = 5., m(2, 1) = 6.;
	testing::internal::CaptureStdout();
	std::cout << m << '\n';
    EXPECT_EQ("((1 2)(3 4)(5 6))\n", 
			testing::internal::GetCapturedStdout());

	DVec v2 = m[1];	 // via row: m[1] -> Row<double, 1> -> DVec
	EXPECT_EQ(v2.size(), 2);
	EXPECT_EQ(v2.dim1(), 2);
}


TEST(struMatrix, slicing)
{
	DVec v(3);  // (1, 2, 3);
	v(0) = 1., v(1) = 2., v(2) = 3.;
	testing::internal::CaptureStdout();
	std::cout << v.slice(1) << '\n';
    EXPECT_EQ("(2 3)\n", 
			testing::internal::GetCapturedStdout());

	DMat m(4, 2);
	m(0, 0) = 1., m(0, 1) = 2., m(1, 0) = 3., m(1, 1) = 4.;
	m(2, 0) = 5., m(2, 1) = 6., m(3, 0) = 7., m(3, 1) = 8.;
	testing::internal::CaptureStdout();
	std::cout << m.slice(1) << '\n';  // starting from row 1
	std::cout << m.slice(1, 3) << '\n';  // from row 1 to 3 (exclusively)
    EXPECT_EQ("((3 4)(5 6)(7 8))\n((3 4)(5 6))\n", 
			testing::internal::GetCapturedStdout());
}


TEST(struMatrix, math)
{
    DMat m32(3, 2); //((1, 2), (3, 4), (5, 6));
	m32(0, 0) = 1., m32(0, 1) = 2., m32(1, 0) = 3., m32(1, 1) = 4., m32(2, 0) = 5., m32(2, 1) = 6.;
    DMat m32b(3, 2); //((4, 5), (6, 7), (8, 9));
	m32b(0, 0) = 4., m32b(0, 1) = 5., m32b(1, 0) = 6., m32b(1, 1) = 7., m32b(2, 0) = 8., m32b(2, 1) = 9.;

    DMat m23(2, 3); //((1, 2, 3), (4, 5, 6));
	m23(0, 0) = 1., m23(0, 1) = 2., m23(0, 2) = 3., m23(1, 0) = 4., m23(1, 1) = 5., m23(1, 2) = 6.;
	DMat m32c(3, 2), m33(3, 3), m44(4, 4);

	DVec v4(4); //(1, 2, 3, 4);
	v4(0) = 1., v4(1) = 2., v4(2) = 3., v4(3) = 4.;
	DVec v4b(4); //(5, 6, 7, 8);
	v4b(0) = 5., v4b(1) = 6., v4b(2) = 7., v4b(3) = 8.;

	// vektor multiplication
	m44 = v4 * v4b;
	testing::internal::CaptureStdout();
	std::cout << m44 << '\n';
    EXPECT_EQ("((5 6 7 8)(10 12 14 16)(15 18 21 24)(20 24 28 32))\n", 
			testing::internal::GetCapturedStdout());

	// apply function
	m32b.apply(_times2);  // void _times2(double&)
	testing::internal::CaptureStdout();
	std::cout << m32b << '\n';
    EXPECT_EQ("((8 10)(12 14)(16 18))\n", 
			testing::internal::GetCapturedStdout());
	//     full matrix operation (uses element-wise operation)	
	m32b.apply(m32, Mul_assign<double>());  // void f(double&, const double&)
	testing::internal::CaptureStdout();
	std::cout << m32b << '\n';
    EXPECT_EQ("((8 20)(36 56)(80 108))\n", 
			testing::internal::GetCapturedStdout());

	// matrix addition
	m32b += m32;
	testing::internal::CaptureStdout();
	std::cout << m32b << '\n';
    EXPECT_EQ("((9 22)(39 60)(85 114))\n", 
			testing::internal::GetCapturedStdout());

	m32c = m32 + m32b;
	testing::internal::CaptureStdout();
	std::cout << m32c << '\n';
    EXPECT_EQ("((10 24)(42 64)(90 120))\n", 
			testing::internal::GetCapturedStdout());

	// matrix multiplication
	m33 = m32 * m23;
	testing::internal::CaptureStdout();
	std::cout << m33 << '\n';
    EXPECT_EQ("((9 12 15)(19 26 33)(29 40 51))\n", 
			testing::internal::GetCapturedStdout());

	// dot product
	EXPECT_EQ(dot_product(v4, v4b), 70);

	// scale and add
	DVec v4c(4);
	testing::internal::CaptureStdout();
	v4c = scale_and_add(v4, 2., v4b);
	std::cout << v4c << '\n';
    EXPECT_EQ("(7 10 13 16)\n", 
			testing::internal::GetCapturedStdout());

	m32c[1].slice(1) = scale_and_add(m32[1].slice(1), 2., m32b[2].slice(1));
	testing::internal::CaptureStdout();
	std::cout << m32c << '\n';
    EXPECT_EQ("((10 24)(42 122)(90 120))\n", 
			testing::internal::GetCapturedStdout());

	// unary minus
	testing::internal::CaptureStdout();
	std::cout << -m32 << '\n';
    EXPECT_EQ("((-1 -2)(-3 -4)(-5 -6))\n", 
			testing::internal::GetCapturedStdout());
}
