#ifndef MATRIX_IO_H
#define MATRIX_IO_H

#include <iostream>

template<class T, size_type N> 
std::ostream& operator<<(std::ostream& os, const Matrix<T, N>& m)
{
    os << '(';

    for (size_type i = 0; i<m.dim1(); ++i)
	{
        os << Matrix<T,N-1>(m[i]);
	}
    os << ')';
    return os;
}


template<class T> 
std::ostream& operator<<(std::ostream& os, const Matrix<T, 1>& m)
{
    os << '(';

    for (size_type i = 0; i<m.dim1(); ++i)
	{
        os << m(i);
		if(i!= m.dim1()-1) 
			os << ' ';
	}
    os << ')';
    return os;
}

/*
template<class T> std::istream& operator>>(std::istream& is, Matrix<T>& v)
{
    char ch;
    is >> ch;

    if (ch!='{') error("'{' missing in Matrix<T,1> input");

    for (size_type i = 0; i<v.dim1(); ++i)
        is >> v(i);

    is >> ch;

    if (ch!='}') error("'}' missing in Matrix<T,1> input");
  
    return is;
}

//-----------------------------------------------------------------------------

template<class T> std::istream& operator>>(std::istream& is, Matrix<T,2>& m)
{
    char ch;
    is >> ch;

    if (ch!='{') error("'{' missing in Matrix<T,2> input");

    for (size_type i = 0; i<m.dim1(); ++i)
    {
        Matrix<T,1> tmp(m.dim2());
        is >> tmp;
        m[i] = tmp;
    }

    is >> ch;

    if (ch!='}') error("'}' missing in Matrix<T,2> input");

    return is;
}

//-----------------------------------------------------------------------------
*/


#endif
