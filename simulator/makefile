


simulator: input_json.o
	g++ -std=c++11 main.cpp input_json.o -Imiscellaneous -I../solver -I../benchmarks/dbench -I../matrix_stru3 -o simulator

input_json.o:
	g++ -std=c++11 input_json.cpp -Imiscellaneous -Imatrix -o input_json.o -c

clear:
	rm simulator # *o
