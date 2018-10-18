#include "stru2.h"
using namespace stru2;
#include "matrix_math.h"
#include "matrixIO.h"



TEST(stru2Matrix, constructNassign)
{
	// construct with extents
	DVec v3(3);
	EXPECT_EQ(v3.extent(0), 3);
	EXPECT_EQ(v3.descriptor().strides[0], 1);
	EXPECT_EQ(v3.size(), 3);
	testing::internal::CaptureStdout();
	std::cout << v3 << '\n';
    EXPECT_EQ("(0 0 0)\n", 
			testing::internal::GetCapturedStdout());
	
    DMat m23(2, 3);  // also initialized with 0
	EXPECT_EQ(m23.extent(0), 2);
	EXPECT_EQ(m23.extent(1), 3);
	EXPECT_EQ(m23.descriptor().strides[0], 3);
	EXPECT_EQ(m23.descriptor().strides[1], 1);
	EXPECT_EQ(m23.size(), 6);

	DTen t234(2, 3, 4);
	EXPECT_EQ(t234.extent(0), 2);
	EXPECT_EQ(t234.extent(1), 3);
	EXPECT_EQ(t234.extent(2), 4);
	EXPECT_EQ(t234.descriptor().strides[0], 12);
	EXPECT_EQ(t234.descriptor().strides[1], 4);
	EXPECT_EQ(t234.descriptor().strides[2], 1);
	EXPECT_EQ(t234.size(), 24);

	// initializer list
    DVec v5{1, 2, 3, 4, 5};
    DMat m32{{1, 2}, {3, 4}, {5, 6}};
    //DTen t232{{{1, 2}, {3, 4}, {5, 6}}, {{1, 2}, {3, 4}, {5, 6}}};

	testing::internal::CaptureStdout();
	std::cout << v5 << '\n';
	std::cout << m32 << '\n';
	//std::cout << t232 << '\n';
    EXPECT_EQ("(1 2 3 4 5)\n((1 2)(3 4)(5 6))\n", //(1 2 3 4 5 6 1 2 3 4 5 6 )\n", 
			testing::internal::GetCapturedStdout());

	// copy construct
    DMat m32b = m32;

	testing::internal::CaptureStdout();
	std::cout << m32b << '\n';
    EXPECT_EQ("((1 2)(3 4)(5 6))\n", 
			testing::internal::GetCapturedStdout());

	// move constuct
    DMat m32c = std::move(m32b);

	testing::internal::CaptureStdout();
	std::cout << m32c << '\n';
    EXPECT_EQ("((1 2)(3 4)(5 6))\n", 
			testing::internal::GetCapturedStdout());

	// copy assign
    DMat m32d; 
	m32d = m32;

	testing::internal::CaptureStdout();
	std::cout << m32d << '\n';
    EXPECT_EQ("((1 2)(3 4)(5 6))\n", 
			testing::internal::GetCapturedStdout());

	// move assign
    DMat m32e; 
	m32e = std::move(m32d);

	testing::internal::CaptureStdout();
	std::cout << m32e << '\n';
    EXPECT_EQ("((1 2)(3 4)(5 6))\n", 
			testing::internal::GetCapturedStdout());

	// construct from Matrix_ref
	DVec v2 = m32[1];
	m32(1, 1) = 1;  // no impact since v2 is copy
	testing::internal::CaptureStdout();
	std::cout << v2 << '\n';
    EXPECT_EQ("(3 4)\n", 
			testing::internal::GetCapturedStdout());
	
	// assign from Matrix_ref
	DVec v2b;
	v2b = m32e[1];
	m32e(1, 1) = 1;  // no impact since vb2 is copy
	testing::internal::CaptureStdout();
	std::cout << v2b << '\n';
    EXPECT_EQ("(3 4)\n", 
			testing::internal::GetCapturedStdout());
}


TEST(stru2Matrix, numberN0)
{
	Matrix<double, 0> n(5);
	EXPECT_EQ(n(), 5);

	testing::internal::CaptureStdout();
	std::cout << n.order << '\n';
    EXPECT_EQ("0\n", testing::internal::GetCapturedStdout());

	n = 10;
	EXPECT_EQ(n(), 10);

	const Matrix<double, 0> cn(6);
	EXPECT_EQ(cn(), 6);
}

TEST(stru2Matrix, matrixSlice)
{
    DVec v{1, 2, 3, 4};

	EXPECT_EQ(v.descriptor().start, 0);
	EXPECT_EQ(v.descriptor().size, 4);
	EXPECT_EQ(v.descriptor().extents[0], 4);
	EXPECT_EQ(v.descriptor().strides[0], 1);
	
	/////
    DMat m{{1, 2}, {3, 4}, {5, 6}};

	EXPECT_EQ(m.descriptor().start, 0);
	EXPECT_EQ(m.descriptor().size, 6);
	EXPECT_EQ(m.descriptor().extents[0], 3);
	EXPECT_EQ(m.descriptor().extents[1], 2);
	EXPECT_EQ(m.descriptor().strides[0], 2);
	EXPECT_EQ(m.descriptor().strides[1], 1);

	/////	
	Matrix_ref<double, 1>  vr = m[1];//.row(1); 	
	EXPECT_EQ(vr.descriptor().start, 2);
	EXPECT_EQ(vr.descriptor().size, 2);
	EXPECT_EQ(vr.descriptor().extents[0], 2);
	EXPECT_EQ(vr.descriptor().strides[0], 1);

	DTen t234(5, 3, 4);
	EXPECT_EQ(t234.extent(0), 5);
	EXPECT_EQ(t234.extent(1), 3);
	EXPECT_EQ(t234.extent(2), 4);
	EXPECT_EQ(t234.descriptor().strides[0], 12);
	EXPECT_EQ(t234.descriptor().strides[1], 4);
	EXPECT_EQ(t234.descriptor().strides[2], 1);
	EXPECT_EQ(t234.size(), 60);
}


TEST(stru2Matrix, indexing)
{
	DVec v{1, 2, 3};
	EXPECT_EQ(v(1), 2);
	EXPECT_EQ(v[1], 2);

	DMat m{{1, 2}, {3, 4}, {5, 6}};
	DMat m2{{1, 2}, {3, 4}, {5, 6}};

	Matrix_ref<double, 1> mr = m[2];  // calls row()
	EXPECT_EQ(mr.descriptor().start, 4);
	EXPECT_EQ(mr.descriptor().size, 2);
	EXPECT_EQ(mr.descriptor().extents[0], 2);
	EXPECT_EQ(mr.descriptor().strides[0], 1);
	//testing::internal::CaptureStdout();
	//std::cout << mr << '\n';
    //EXPECT_EQ("(5 6 )\n", 
	//		testing::internal::GetCapturedStdout());
	m(2, 1) = 10;
	EXPECT_EQ(mr(1), 10);  // reference - not copy
	// copy
	DVec v2 = m[1];	
	EXPECT_EQ(v2.descriptor().start, 0);  // ???
	EXPECT_EQ(v2.descriptor().size, 2);
	EXPECT_EQ(v2.descriptor().extents[0], 2);
	EXPECT_EQ(v2.descriptor().strides[0], 1);
	m(1, 1) = 10;  // does not impact v2
	testing::internal::CaptureStdout();
	std::cout << v2 << '\n';
    EXPECT_EQ("(3 4)\n", 
			testing::internal::GetCapturedStdout());
}



TEST(stru2Matrix, math)
{
    DMat m32{{1, 2}, {3, 4}, {5, 6}};
    DMat m32b{{4, 5}, {6, 7}, {8, 9}};

    DMat m23{{1, 2, 3}, {4, 5, 6}};
	DMat m32c, m33, m44;

	DVec v4{1, 2, 3, 4};
	DVec v4b{5, 6, 7, 8};

	// vektor multiplication
	m44 = v4 * v4b;
	testing::internal::CaptureStdout();
	std::cout << m44 << '\n';
    EXPECT_EQ("((5 6 7 8)(10 12 14 16)(15 18 21 24)(20 24 28 32))\n", 
			testing::internal::GetCapturedStdout());

	// apply function
	m32b.apply([](double& x) { x *= 2; } );
	testing::internal::CaptureStdout();
	std::cout << m32b << '\n';
    EXPECT_EQ("((8 10)(12 14)(16 18))\n", 
			testing::internal::GetCapturedStdout());
	
	m32b.apply(m32, [](double& x, const double& y) { x += 2*y; } );
	testing::internal::CaptureStdout();
	std::cout << m32b << '\n';
    EXPECT_EQ("((10 14)(18 22)(26 30))\n", 
			testing::internal::GetCapturedStdout());

	// matrix addition
	m32b += m32;
	testing::internal::CaptureStdout();
	std::cout << m32b << '\n';
    EXPECT_EQ("((11 16)(21 26)(31 36))\n", 
			testing::internal::GetCapturedStdout());

	/*m32c = m32 + m32b;
	testing::internal::CaptureStdout();
	std::cout << m32c << '\n';
    EXPECT_EQ("((12 18)(24 30)(36 42))\n", 
			testing::internal::GetCapturedStdout());
	*/
	// matrix multiplication
	m33 = m32 * m23;
	testing::internal::CaptureStdout();
	std::cout << m33 << '\n';
    EXPECT_EQ("((9 12 15)(19 26 33)(29 40 51))\n", 
			testing::internal::GetCapturedStdout());

	// dot product
	EXPECT_EQ(dot_product(v4, v4b), 70);
}

