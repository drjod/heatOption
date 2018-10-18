#ifndef MATRIX_ERROR_H
#define MATRIX_ERROR_H

#include <string>


struct Matrix_error {
    std::string name;
    Matrix_error(const char* q) :name(q) { }
    Matrix_error(std::string n) :name(n) { }
};

//-----------------------------------------------------------------------------

inline void error(const char* p)
{
    throw Matrix_error(p);
}

#endif
