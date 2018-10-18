//#include "bcgs.h"


TEST(bcgs, all)
{
	
	//DMat A{{2, 1, -1},{-3, -1, 2},{-2, 1, 2}};
	//DVec b{8, -11, -3};
	//DVec x{1, 1, 1};

    DMat A(3, 3);
    DVec b(3), x(3);
    A(0, 0) = 2., A(0, 1) = 1., A(0, 2) = -1.;
    A(1, 0) = -3., A(1, 1) = -1., A(1, 2) = 2.;
    A(2, 0) = -2., A(2, 1) = 1., A(2, 2) = 2.;
    b[0] = 8., b[1] = -11., b[2] = -3.;
    x[0] = 1., x[1] = 1., x[2] = 1.;

	testing::internal::CaptureStdout();
	bcgs(A, b, x);
    EXPECT_EQ("Iterations: 3\n", 
			testing::internal::GetCapturedStdout());

	testing::internal::CaptureStdout();
	std::cout << x << '\n';
    EXPECT_EQ("(2 3 -1)\n", 
			testing::internal::GetCapturedStdout());

}
