#!/bin/bash

bash build.sh


echo "**********************"
echo "**** TESTING STRU ****"
echo "**********************"
build/run_struTests

echo "***********************"
echo "**** TESTING STRU2 ****"
echo "***********************"
build/run_stru2Tests

echo "***********************"
echo "**** TESTING STRU3 ****"
echo "***********************"
build/run_stru3Tests



