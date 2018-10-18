GTESTPATH=/home/jens/git/googletest/googletest/scripts/gtest
INCLUDE=-I/home/jens/git/googletest/googletest/scripts -I../matrix_stru -I../matrix_stru2 -I../matrix_stru3 -I../solver -I../setups -I../supplements
CXXFLAGS=$(INCLUDE) -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP
CXXFLAGS_CPP14=-std=c++14 $(INCLUDE) $(CXXFLAGS)
STRUFLAGS=

all: testing_stru testing_stru2 testing_stru3


testing_stru: allStruTests.o $(GTESTPATH)/gtest-all.o
	$(CXX) -pthread -o $@ $+ 

testing_stru2: allStru2Tests.o $(GTESTPATH)/gtest-all.o
	$(CXX) -pthread -o $@ $+ 

testing_stru3: allStru3Tests.o $(GTESTPATH)/gtest-all.o
	$(CXX) -pthread -o $@ $+ 

allStruTests.o: allStruTests.cpp test_stru.cpp test_gauss.cpp test_bcgs.cpp # ../matrix_stru/stru_matrix.h
	$(CXX) $(STRUFLAGS) $(CXXFLAGS) -MF"allTests.d" -MT"allTests.d" -o $@ $<

allStru2Tests.o: allStru2Tests.cpp test_stru2.cpp test_stru2_ref.cpp test_gauss.cpp test_bcgs.cpp # ../matrix_stru2/stru2_matrix.h
	$(CXX) $(CXXFLAGS_CPP14) -MF"allTests.d" -MT"allTests.d" -o $@ $<

allStru3Tests.o: allStru3Tests.cpp test_stru3.cpp test_gauss.cpp test_bcgs.cpp # ../matrix_stru3/stru3_matrix.h
	$(CXX) $(CXXFLAGS_CPP14) -MF"allTests.d" -MT"allTests.d" -o $@ $<

$(GTESTPATH)/gtest-all.o: $(GTESTPATH)/gtest-all.cc
	$(CXX) $(CXXFLAGS_CPP14) -MF"$(GTESTPATH)/gtest-all.d" -MT"$(GTESTPATH)/gtest-all.d" -o $@ $<                   


clear:
	rm testing_str* *.o *.d 2> /dev/null || echo > /dev/null

