
#include <typeinfo>

#include "stru2.h"
using namespace stru2;
#include "matrix_math.h"
#include "matrixIO.h"



TEST(stru2Matrix_ref, FromDMat)
{
	// 1 dim Ref from 2D matrix
	DMat m33{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
	Matrix_ref<double, 1> m33a = m33[1];
	Matrix_ref<double, 1> m33b = m33[2];

	EXPECT_EQ(m33.descriptor().start, 0);
	EXPECT_EQ(m33.descriptor().size, 9);
	EXPECT_EQ(m33.descriptor().extents[0], 3);
	EXPECT_EQ(m33.descriptor().extents[1], 3);
	EXPECT_EQ(m33.descriptor().strides[0], 3);
	EXPECT_EQ(m33.descriptor().strides[1], 1);

	EXPECT_EQ(m33a.descriptor().start, 3);
	EXPECT_EQ(m33a.descriptor().size, 3);
	EXPECT_EQ(m33a.descriptor().extents[0], 3);
	EXPECT_EQ(m33a.descriptor().strides[0], 1);

	EXPECT_EQ(m33b.descriptor().start, 6);
	EXPECT_EQ(m33b.descriptor().size, 3);
	EXPECT_EQ(m33b.descriptor().extents[0], 3);
	EXPECT_EQ(m33b.descriptor().strides[0], 1);

	EXPECT_EQ(m33b(slice(1, 2)).descriptor().start, 7);
	EXPECT_EQ(m33b(slice(1, 2)).descriptor().size, 2);
	EXPECT_EQ(m33b(slice(1, 2)).descriptor().extents[0], 2);
	EXPECT_EQ(m33b(slice(1, 2)).descriptor().strides[0], 1);

	/*testing::internal::CaptureStdout();
	std::cout << m33a << '\n';
    EXPECT_EQ("(4 5 6 )\n", 
			testing::internal::GetCapturedStdout());
	testing::internal::CaptureStdout();
	std::cout << m33b << '\n';
    EXPECT_EQ("(7 8 9 )\n", 
			testing::internal::GetCapturedStdout());
*/
	// then convert 1D ref to 1D vector
	DVec v3a = m33a;
	DVec v3b = m33b;
	testing::internal::CaptureStdout();
	std::cout << v3a << v3b << '\n';
    EXPECT_EQ("(4 5 6)(7 8 9)\n", 
			testing::internal::GetCapturedStdout());

	// 2 dim
/*	Matrix_ref<double, 2> m33r = m33(1, slice(1,2));
	testing::internal::CaptureStdout();
	std::cout << m33r << '\n';
    EXPECT_EQ("(5 6 )\n", 
			testing::internal::GetCapturedStdout());

	EXPECT_EQ(m33r(0, 0), 5);
	//EXPECT_EQ(m33r(0, 1), 6);  // ???

	// math - add
	Matrix_ref<double, 2> m33r2 = m33(2, slice(1,2));
	testing::internal::CaptureStdout();
	std::cout << m33r2 << '\n';
    EXPECT_EQ("(8 9 )\n", 
			testing::internal::GetCapturedStdout());

	testing::internal::CaptureStdout();
	std::cout << m33r + m33r2 << '\n';
    EXPECT_EQ("(13 15 )\n", 
			testing::internal::GetCapturedStdout());

	std::cout << m33r.descriptor() << '\n';
*/
}


TEST(stru2Matrix_ref, math)
{


	// scale and add
	DMat m34{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
	m34[1](slice(1, 3)) = scale_and_add(m34[2](slice(1, 3)), 2., m34[0](slice(0, 3)));
	testing::internal::CaptureStdout();
	std::cout << m34 << '\n';
    EXPECT_EQ("((1 2 3 4)(5 21 24 27)(9 10 11 12))\n", 
			testing::internal::GetCapturedStdout());

	// dot product
	EXPECT_EQ(dot_product(m34[2](slice(1, 3)), m34[2](slice(0,3))), 332);



//std::cout<< scale_and_add(m3[2](slice(0, 2)), 0., m3[1](slice(0, 2))).descriptor() << "\n";
	//testing::internal::CaptureStdout();
	//std::cout << m3 << '\n';
}


