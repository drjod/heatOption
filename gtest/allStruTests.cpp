#include "gtest/gtest.h"

#include "test_stru.cpp"


#include "gauss.h"
#include "bcgs.h"

#include "test_gauss.cpp"
#include "test_bcgs.cpp"



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

