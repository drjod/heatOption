// based on stroustup Matrix.h

#ifndef STRU_MATRIX_H
#define STRU_MATRIX_H

// #define LOGGING
// #define CPP11

#ifdef LOGGING
#include <iostream>
	#define LOG(x) std::cout << x << '\n'
#else
	#define LOG(x)
#endif


#ifdef CPP11
	#include <initializer_list>
	// #include "matrix_init.h"
#endif

#include "matrix_error.h"

namespace stru
{

typedef long size_type;

template<class T, size_type> class Matrix;
typedef Matrix<double, 1> DVec;
typedef Matrix<double, 2> DMat;
typedef Matrix<double, 3> DTen;

//-----------------------------------------------------------------------------
/*
// The general Matrix template is simply a prop for its specializations:
template<class T = double, size_type D = 1> class Matrix {
    // multidimensional matrix class
    // ( ) does multidimensional subscripting
    // [ ] does C style "slicing": gives an N-1 dimensional matrix from an N dimensional one
    // row() is equivalent to [ ]
    // column() is not (yet) implemented because it requires strides.
    // = has copy semantics
    // ( ) and [ ] are range checked
    // slice() to give sub-ranges 
private:
    Matrix();    // this should never be compiled
};
*/

//-----------------------------------------------------------------------------

template<class T = double, size_type D = 1> class Row ;    // forward declaration

// actually seems not to be helpfull concerning performance
template<class T, size_type N> Matrix<T,N> xfer(Matrix<T,N>& a)
{	
    return a.xfer();
}

//-----------------------------------------------------------------------------
#include "matrixET.h"  // expression templates
#include "stru_base.h"  // here are the data
#include "stru_math.h" // math operations (only the member functions and functors)
#include "stru_1.h"  // vector
#include "stru_2.h"  // matrix
#include "stru_3.h"  // tensor
#include "stru_row.h"  // used for slicing
//-----------------------------------------------------------------------------

}  // end namespace

#endif

