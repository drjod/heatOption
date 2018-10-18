#include <iostream>

//#include "gauss.h"
//#include "bcgs.h"

void assemble_matrix(DMat& A, DVec& b, int grid_size)
{
	//A = DMat(grid_size, grid_size);
	//b = DVec(grid_size);

	for(size_type i=1; i<grid_size-1; ++i)
		A(i, i) = 1;

	for(size_type i=1; i<grid_size-1; ++i)
		A(i, i+1) = -0.5;

	for(size_type i=1; i<grid_size-1; ++i)
		A(i, i-1) = -0.5;

}


void solve(int grid_size)
{
//for(int i=0; i<10; ++i)
{
	DMat A(grid_size, grid_size);
	DVec b(grid_size);
	DVec x(grid_size);
	x[0] = 1.;
	double accuracy;

	assemble_matrix(A, b, grid_size);
	accuracy = bcgs(A, b, x);
    
	//classical_elimination(A, b);
	//x = back_substitution(A, b);
	//std::cout << x << '\n';
	//std::cout << accuracy << '\n';
}

}




