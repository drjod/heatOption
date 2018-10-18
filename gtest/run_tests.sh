#!/bin/bash

make clear
if [ "$1" = "c++11" ]; then
	make STRUFLAG=-std=c++11
else
	make
fi


echo "**********************"
echo "**** TESTING STRU ****"
echo "**********************"
./testing_stru

echo "***********************"
echo "**** TESTING STRU2 ****"
echo "***********************"
./testing_stru2

echo "***********************"
echo "**** TESTING STRU3 ****"
echo "***********************"
./testing_stru3



