#ifndef STRU_MATRIX_MATH_H
#define STRU_MATRIX_MATH_H

// some functors

template<class T> struct Assign { void operator()(T& a, const T& c) { a = c; } };
template<class T> struct Add_assign { void operator()(T& a, const T& c) { a += c; } };
template<class T> struct Mul_assign { void operator()(T& a, const T& c) { a *= c; } };
template<class T> struct Sub_assign { void operator()(T& a, const T& c) { a -= c; } };
template<class T> struct Div_assign { void operator()(T& a, const T& c) { a /= c; } };
template<class T> struct Mod_assign { void operator()(T& a, const T& c) { a %= c; } };
template<class T> struct Or_assign { void operator()(T& a, const T& c) { a |= c; } };
template<class T> struct Xor_assign { void operator()(T& a, const T& c) { a ^= c; } };
template<class T> struct And_assign { void operator()(T& a, const T& c) { a &= c; } };
template<class T> struct Not_assign { void operator()(T& a) { a = !a; } };
template<class T> struct Not { T operator()(T& a) { return !a; } };
template<class T> struct Unary_minus { T operator()(T& a) { return -a; } };
template<class T> struct Complement { T operator()(T& a) { return ~a; } };

//-----------------------------------------------------------------------------

template<typename Matrix, typename T>
class Matrix_math
{
public:
    // element-wise operations:
    template<class F> Matrix& apply(F f) { static_cast<Matrix*>(this)->base_apply(f); return *static_cast<Matrix*>(this); }
    template<class F> Matrix& apply(F f,const T& c) { static_cast<Matrix*>(this)->base_apply(f,c); return *static_cast<Matrix*>(this); }

    Matrix& operator*=(const T& c) { static_cast<Matrix*>(this)->base_apply(Mul_assign<T>(),c);   return *static_cast<Matrix*>(this); }
    Matrix& operator/=(const T& c) { static_cast<Matrix*>(this)->base_apply(Div_assign<T>(),c);   return *static_cast<Matrix*>(this); }
    Matrix& operator%=(const T& c) { static_cast<Matrix*>(this)->base_apply(Mod_assign<T>(),c);   return *static_cast<Matrix*>(this); }
    Matrix& operator+=(const T& c) { static_cast<Matrix*>(this)->base_apply(Add_assign<T>(),c);   return *static_cast<Matrix*>(this); }
    Matrix& operator-=(const T& c) { static_cast<Matrix*>(this)->base_apply(Sub_assign<T>(),c); return *static_cast<Matrix*>(this); }

    Matrix& operator&=(const T& c) { static_cast<Matrix*>(this)->base_apply(And_assign<T>(),c);   return *static_cast<Matrix*>(this); }
    Matrix& operator|=(const T& c) { static_cast<Matrix*>(this)->base_apply(Or_assign<T>(),c);    return *static_cast<Matrix*>(this); }
    Matrix& operator^=(const T& c) { static_cast<Matrix*>(this)->base_apply(Xor_assign<T>(),c);   return *static_cast<Matrix*>(this); }

    Matrix operator!()  { Matrix m( *static_cast<Matrix*>(this), Not<T>() );; return m;} //  return xfer(m); }  // trust copy elision
    Matrix operator-() { Matrix m( *static_cast<Matrix*>(this), Unary_minus<T>() ); return m;} //return xfer(m); }
    Matrix operator~()  { Matrix m( *static_cast<Matrix*>(this), Complement<T>() );; return m;} //  return xfer(m); }

	// full matrix operations
	template<typename F>                                                                                          
	Matrix& apply(const Matrix& m, F f)                                                  
	{                                                                                                             
		LOG("Matrix 1: Apply binary function to elements");
        for (size_type i = 0; i<static_cast<Matrix*>(this)->sz; ++i) f(static_cast<Matrix*>(this)->elem[i],  m.elem[i]); 
		return *static_cast<Matrix*>(this);                                                                                             
	} 

	// addition                                                                                                   
	Matrix& operator+=(const Matrix& m)                                                 
	{                                                                                                             
		apply(m, Add_assign<T>());
		return *static_cast<Matrix*>(this);                                                                                             
	}                                                                                                             
	// subtraction                                                                                                
	Matrix& operator-=(const Matrix& m)                                                 
	{                                                                                                             
		apply(m, Sub_assign<T>());
		return *static_cast<Matrix*>(this);                                                                                             
	}     
    template<class F> Matrix apply_new(F f) { return xfer(Matrix(*static_cast<Matrix*>(this),f)); }

	// swapping    
    void swap_rows(size_type i, size_type j)
        // swap_rows() uses a row's worth of memory for better run-time performance
        // if you want pairwise swap, just write it yourself
    {
        if (i == j) return;
    /*
        Matrix<T,1> temp = (*static_cast<Matrix*>(this))[i];
        (*static_cast<Matrix*>(this))[i] = (*static_cast<Matrix*>(this))[j];
        (*static_cast<Matrix*>(this))[j] = temp;
    */
        size_type max = (*static_cast<Matrix*>(this))[i].size();
        for (size_type ii=0; ii<max; ++ii) std::swap((*static_cast<Matrix*>(this))(i,ii),(*static_cast<Matrix*>(this))(j,ii));
    }
};

//-----------------------------------------------------------------------------

template<class T, size_type D> Matrix<T,D> operator*(const Matrix<T,D>& m, const T& c) { Matrix<T,D> r(m); return r*=c; }
template<class T, size_type D> Matrix<T,D> operator/(const Matrix<T,D>& m, const T& c) { Matrix<T,D> r(m); return r/=c; }
template<class T, size_type D> Matrix<T,D> operator%(const Matrix<T,D>& m, const T& c) { Matrix<T,D> r(m); return r%=c; }
template<class T, size_type D> Matrix<T,D> operator+(const Matrix<T,D>& m, const T& c) { Matrix<T,D> r(m); return r+=c; }
template<class T, size_type D> Matrix<T,D> operator-(const Matrix<T,D>& m, const T& c) { Matrix<T,D> r(m); return r-=c; }

template<class T, size_type D> Matrix<T,D> operator&(const Matrix<T,D>& m, const T& c) { Matrix<T,D> r(m); return r&=c; }
template<class T, size_type D> Matrix<T,D> operator|(const Matrix<T,D>& m, const T& c) { Matrix<T,D> r(m); return r|=c; }
template<class T, size_type D> Matrix<T,D> operator^(const Matrix<T,D>& m, const T& c) { Matrix<T,D> r(m); return r^=c; }

//-----------------------------------------------------------------------------

// xfer removed since the compiler does copy elision                                                                       
template<class F, class A>            A apply(F f, A x)        { A res(x,f);   return res; } // xfer(res); }  
template<class F, class Arg, class A> A apply(F f, A x, Arg a) { A res(x,f,a); return res; } // xfer(res); }  
              

#endif
