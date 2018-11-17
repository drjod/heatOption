cmake_minimum_required(VERSION 2.6)
project(heatOption)
set(heatOption__VERSION_MAJOR 1)
set(heatOption_VERSION_MINOR 0)


include_directories(                                                                                          
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/matrix_stru"
        "${PROJECT_SOURCE_DIR}/matrix_stru2"
        "${PROJECT_SOURCE_DIR}/matrix_stru3"
        "${PROJECT_SOURCE_DIR}/solver"
        "${PROJECT_SOURCE_DIR}/supplements"
        "${PROJECT_SOURCE_DIR}/simulator"
        "${PROJECT_SOURCE_DIR}/simulator/miscellaneous"
        "${PROJECT_SOURCE_DIR}/benchmarks/dbench"
) 

set(CMAKE_CXX_FLAGS "-Wall -pthread -fopenmp")
set(CMAKE_CXX_STANDARD 14)

add_subdirectory("${PROJECT_SOURCE_DIR}/ext/gtest-1.8.0")

enable_testing()

include_directories(
		"${PROJECT_SOURCE_DIR}"
		"${gtest_SOURCE_DIR}"
		"${gtest_SOURCE_DIR}/include"
)

add_executable(run_struTests gtest/allStruTests.cpp)
target_link_libraries(run_struTests gtest gtest_main) 

add_executable(run_stru2Tests gtest/allStru2Tests.cpp)
target_link_libraries(run_stru2Tests gtest gtest_main) 

add_executable(run_stru3Tests gtest/allStru3Tests.cpp)
target_link_libraries(run_stru3Tests gtest gtest_main) 

add_subdirectory(simulator)
add_executable(simulate simulator/main.cpp)
target_link_libraries(simulate input_json) 



