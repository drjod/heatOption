#include "dbench.h"
#include "benchmarking_stru3.cpp"


int main()
{
	//benchmarking::collection.add_function(benchmarking::matrixAdditionSubtractionChain, "matrixAdditionSubtractionChain", 1);
	benchmarking::collection.add_function(benchmarking::matrixDoubleMultiplication, "matrixDoubleMultiplication", 3);
	benchmarking::collection.add_function(benchmarking::matrixVectorMultiplication, "matrixVectorMultiplication", 3);
	//benchmarking::collection.add_function(benchmarking::matrixVectorMultiplication, "matrixMatrixMultiplication", 1);
	//benchmarking::collection.add_function(benchmarking::matrixVectorMultiplication, "functionOnMatrices", 1);
	benchmarking::collection.add_function(benchmarking::scaleAndAddVectors, "scaleAndAddVectors", 1);
	benchmarking::collection.add_function(benchmarking::scaleAndAddRows, "scaleAndAddRows", 1);
	benchmarking::collection.add_function(benchmarking::vectorAddition, "VectorAddition", 10);
	//benchmarking::collection.add_function(benchmarking::matrixMultiplication, "matrixMultiplication", 1);
	//benchmarking::collection.add_function(benchmarking::doubleMatrixMultiplication, "doubleMatrixMultiplication", 2);
	benchmarking::collection.add_function(benchmarking::gauss, "gauss", 3);
	benchmarking::collection.add_function(benchmarking::bcgs, "bcgs", 3);

	benchmarking::collection.run();

	return 0;
}
