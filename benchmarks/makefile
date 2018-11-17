INCLUDE=-Idbench -I../matrix_stru -I../matrix_stru2 -I../matrix_stru3 -I../solver -I../setups -I../supplements
CXXFLAGS= $(INCLUDE) -O3 -Wall -fopenmp 
#-std=c++11

all: allStruBenchmarks allStru3Benchmarks

allStruBenchmarks: allStruBenchmarks.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ allStruBenchmarks.cpp

allStru3Benchmarks: allStru3Benchmarks.cpp
	$(CXX) $(CXXFLAGS) -std=c++11 $(INCLUDE) -o $@ allStru3Benchmarks.cpp

# benchmarking_stru.o: benchmarking_stru_bcgs.cpp
# 	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $+


clear:
	rm allStruBenchmarks allStru3Benchmarks *.o *.d 2> /dev/null || echo > /dev/null

