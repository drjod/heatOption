//#include "gauss.h"


TEST(gauss, small)
{
	//DMat A{{2, 1, -1},{-3, -1, 2},{-2, 1, 2}};
	//DVec b{8, -11, -3}, x(3);

    DMat A(3, 3);
    DVec b(3), x(3);
    A(0, 0) = 2., A(0, 1) = 1., A(0, 2) = -1.;
    A(1, 0) = -3., A(1, 1) = -1., A(1, 2) = 2.;
    A(2, 0) = -2., A(2, 1) = 1., A(2, 2) = 2.;
    b[0] = 8., b[1] = -11., b[2] = -3.;
	//x = 0.;

	classical_elimination(A, b);
	x = back_substitution(A, b);

	testing::internal::CaptureStdout();
	std::cout << A << '\n';
    EXPECT_EQ("((2 1 -1)(0 0.5 0.5)(0 0 -1))\n", 
			testing::internal::GetCapturedStdout());

	testing::internal::CaptureStdout();
	std::cout << b << '\n';
    EXPECT_EQ("(8 1 1)\n", 
			testing::internal::GetCapturedStdout());

	testing::internal::CaptureStdout();
	std::cout << x << '\n';
    EXPECT_EQ("(2 3 -1)\n", 
			testing::internal::GetCapturedStdout());


}



TEST(gauss, large)
{
	const long size = 100;

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
	b[0] = 2;
	b[size-1] = 1;

	classical_elimination(A, b);
	x = back_substitution(A, b);

//	std::cout << x << '\n';
}
