#include "gtest/gtest.h"


#include "test_stru2.cpp"
#include "test_stru2_ref.cpp"

// #include "gauss.h"
// #include "bcsg.h"

//#include "test_gauss.cpp"
//#include "test_bcgs.cpp"



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

