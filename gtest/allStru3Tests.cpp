#include "gtest/gtest.h"

#include <iostream>
#include "test_stru3.cpp"

#include "stru3_gauss.h"
#include "stru3_bcgs.h"

#include "test_gauss.cpp"
#include "test_bcgs.cpp"



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

