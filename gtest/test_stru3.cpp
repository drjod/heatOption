#include "stru3_matrix.h"
using namespace stru3;
//#include "matrix_math.h"
//#include "matrixIO.h"



TEST(struMatrix, constructNassign)
{
	// construct with extents
	DVec v3(3);
	v3 = 0.;
	//EXPECT_EQ(v3.dim1(), 3);
	EXPECT_EQ(v3.size(), 3);
	testing::internal::CaptureStdout();
	std::cout << v3 << '\n';
    EXPECT_EQ("(0 0 0)\n", 
			testing::internal::GetCapturedStdout());
	
    DMat m23(2, 3);
	EXPECT_EQ(m23.dim1(), 2);
	EXPECT_EQ(m23.dim2(), 3);
	EXPECT_EQ(m23.size(), 6);

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

	// segmentation fault
	//// std::move 
	//DMat m32d = std::move(m32b);
	//m32d(1,1) = 10.;
	////
	//testing::internal::CaptureStdout();
	//std::cout << m32d << '\n';
    //EXPECT_EQ("((5 5)(5 10)(5 5))\n", 
	//		testing::internal::GetCapturedStdout());

	//DMat m32e(3, 2);
	//m32e = 20.;
	//DMat m32f = std::nove(m32e);  // move constructor
	//m32e = 30.;

	//testing::internal::CaptureStdout();
	//std::cout << m32e << '\n';
	//std::cout << m32f << '\n';


    //EXPECT_EQ("((30 30)(30 30)(30 30))\n((30 30)(30 30)(30 30))\n", 
	//		testing::internal::GetCapturedStdout());

	// construct from pointer (only 1D)
	double* p = new double[2];
	p[0] = 10.;
	p[1] = 11.;
	DVec v2(p, 2);
	testing::internal::CaptureStdout();
	std::cout << v2 << '\n';
    EXPECT_EQ("(10 11)\n", 
			testing::internal::GetCapturedStdout());

	// initialier list
	DVec v3b = {1., 2., 3.};
	testing::internal::CaptureStdout();
	std::cout << v3b << '\n';
    EXPECT_EQ("(1 2 3)\n", 
			testing::internal::GetCapturedStdout());

	DMat m32d = {{1., 2.}, {3., 4.},{5., 6.}};
	testing::internal::CaptureStdout();
	std::cout << m32d << '\n';
    EXPECT_EQ("((1 2)(3 4)(5 6))\n", 
			testing::internal::GetCapturedStdout());
}

TEST(struMatrix, indexing)
{
	DVec v(3);  // (1, 2, 3);
	v[0] = 1., v[1] = 2., v[2] = 3.;  // only fortran indexing
	EXPECT_EQ(v[1], 2);

	DMat m(3, 2);
	m(0, 0) = 1., m(0, 1) = 2., m(1, 0) = 3., m(1, 1) = 4., m(2, 0) = 5., m(2, 1) = 6.;
	testing::internal::CaptureStdout();
	std::cout << m << '\n';
    EXPECT_EQ("((1 2)(3 4)(5 6))\n", 
			testing::internal::GetCapturedStdout());
}

struct geo
{
	enum type { hex, pris };
	int return_1() const { return 1; }
};

TEST(struMatrix, slicing)
{
	// Slice_iter
	DMat m{{1., 2.}, {3., 4.}, {5., 6.}};
	Slice_iter<double> s = m[1];
	s[1] = 10.;
	testing::internal::CaptureStdout();
	std::cout << s << '\n';
    EXPECT_EQ("(3 10)\n", 
			testing::internal::GetCapturedStdout());

	Slice_iter<double> sc = m.column(1);
	testing::internal::CaptureStdout();
	std::cout << sc << '\n';
    EXPECT_EQ("(2 10 6)\n", 
			testing::internal::GetCapturedStdout());

	EXPECT_EQ(*sc, 2);
	EXPECT_EQ(*(++sc), 10);
	EXPECT_EQ(*(sc++), 10);
	EXPECT_EQ(*sc, 6);
	EXPECT_EQ(sc(0), 2);
	EXPECT_EQ(sc[0], 2);

	testing::internal::CaptureStdout();
	for(Slice_iter<double> s2(m[1]); s2 != s2.end(); ++s2)
		std::cout << *s2 << " ";
    EXPECT_EQ("3 10 ", 
			testing::internal::GetCapturedStdout());

	// member access (operator->)
    std::valarray<geo> vg(10);                                                                                
    Slice_iter<geo> it_g(&vg, std::slice(5, 5, 1));                                                           
    EXPECT_EQ(it_g->return_1(), 1);

	// Cslice_iter
	const DMat cm{{1., 2.}, {3., 4.}, {5., 6.}};
	Cslice_iter<double> cs = cm[1];
	testing::internal::CaptureStdout();
	std::cout << cs << '\n';
    EXPECT_EQ("(3 4)\n", 
			testing::internal::GetCapturedStdout());

	cs = cm.row(2);
	testing::internal::CaptureStdout();
	std::cout << cs << '\n';
    EXPECT_EQ("(5 6)\n", 
			testing::internal::GetCapturedStdout());

	cs = cm.column(1);
	testing::internal::CaptureStdout();
	std::cout << cs << '\n';
    EXPECT_EQ("(2 4 6)\n", 
			testing::internal::GetCapturedStdout());

	EXPECT_EQ(*cs, 2);
	EXPECT_EQ(*(++cs), 4);
	EXPECT_EQ(*(cs++), 4);
	EXPECT_EQ(*cs, 6);
	EXPECT_EQ(cs(0), 2);
	EXPECT_EQ(cs[0], 2);

	testing::internal::CaptureStdout();
	for(Cslice_iter<double> cs2(cm[1]); cs2 != cs2.end(); ++cs2)
		std::cout << *cs2 << " ";
    EXPECT_EQ("3 4 ", 
			testing::internal::GetCapturedStdout());

	// member access (operator->)
    const std::valarray<geo> cvg(10);
	Cslice_iter<geo> it_cg(&cvg, std::slice(5, 5, 1));                                                           
    EXPECT_EQ(it_cg->return_1(), 1);
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

	/*DVec v4(4); //(1, 2, 3, 4);
	v4[0] = 1., v4[1] = 2., v4[2] = 3., v4[3] = 4.;
	DVec v4b(4); //(5, 6, 7, 8);
	v4b[0] = 5., v4b[1] = 6., v4b[2] = 7., v4b[3] = 8.;
*/
	std::valarray<double> v4(4);
	v4[0] = 1., v4[1] = 2., v4[2] = 3., v4[3] = 4.;
	std::valarray<double> v4b(4);
	v4b[0] = 5., v4b[1] = 6., v4b[2] = 7., v4b[3] = 8.;

	std::valarray<double> v2(2);
	v2[0] = 1., v2[1] = 2.;

	// vektor multiplication
	//m44 = v4 * v4b;
	//testing::internal::CaptureStdout();
	//std::cout << m44 << '\n';
    //EXPECT_EQ("((5 6 7 8)(10 12 14 16)(15 18 21 24)(20 24 28 32))\n", 
	//		testing::internal::GetCapturedStdout());


	// apply function
	//m32b.apply(_times2);  // void _times2(double&)
	//testing::internal::CaptureStdout();
	//std::cout << m32b << '\n';
    //EXPECT_EQ("((8 10)(12 14)(16 18))\n", 
	//		testing::internal::GetCapturedStdout());
	////     full matrix operation (uses element-wise operation)	
	//m32b.apply(m32, Mul_assign<double>());  // void f(double&, const double&)
	//testing::internal::CaptureStdout();
	//std::cout << m32b << '\n';
    //EXPECT_EQ("((8 20)(36 56)(80 108))\n", 
	//		testing::internal::GetCapturedStdout());

	// matrix addition
	//m32b += m32;
	//testing::internal::CaptureStdout();
	//std::cout << m32b << '\n';
    //EXPECT_EQ("((9 22)(39 60)(85 114))\n", 
	//		testing::internal::GetCapturedStdout());

	//m32c = m32 + m32b;
	//testing::internal::CaptureStdout();
	//std::cout << m32c << '\n';
    //EXPECT_EQ("((10 24)(42 64)(90 120))\n", 
	//		testing::internal::GetCapturedStdout());

	// matrix-vektor multiplication
	std::valarray<double> v3(3);
	v3 =  m32 * v2;
	testing::internal::CaptureStdout();
	std::cout << v3 << '\n';
    EXPECT_EQ("(5 11 17)\n", 
			testing::internal::GetCapturedStdout());

/*
	// matrix multiplication
	m33 = m32 * m23;
	testing::internal::CaptureStdout();
	std::cout << m33 << '\n';
    EXPECT_EQ("((9 12 15)(19 26 33)(29 40 51))\n", 
			testing::internal::GetCapturedStdout());

	// dot product
	EXPECT_EQ(dot_product(v4, v4b), 70);

*/
	// scale and add
	DVec v4c(4);
	testing::internal::CaptureStdout();
	v4c = scale_and_add(v4, 2., v4b);
	std::cout << v4c << '\n';
    EXPECT_EQ("(7 10 13 16)\n", 
			testing::internal::GetCapturedStdout());

	m32c[1] = scale_and_add(m32[1], 2., m32b[2]);
	testing::internal::CaptureStdout();
	std::cout << m32c << '\n';
    EXPECT_EQ("((0 0)(14 17)(0 0))\n", 
			testing::internal::GetCapturedStdout());

/*
	// unary minus
	testing::internal::CaptureStdout();
	std::cout << -m32 << '\n';
    EXPECT_EQ("((-1 -2)(-3 -4)(-5 -6))\n", 
			testing::internal::GetCapturedStdout());
*/
}

