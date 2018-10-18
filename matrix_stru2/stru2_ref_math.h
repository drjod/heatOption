
#include "stru2.h"

// math operations                                                                                            
//    add                                                                                                     
template<typename T, size_type N>                                                                             
template<typename F>                                                                                          
Matrix_ref<T, N>& Matrix_ref<T, N>::apply(F f)                                                                        
{                                                                                                             
    for(size_type i = desc.start; i!= desc.start+desc.size; ++i) f(ptr[i]);                                                                                
    return *this;                                                                                             
}                                                                                                             

                                                                                                              
template<typename T, size_type N>                                                                             
template<typename F>                                                                                          
Matrix_ref<T, N>& Matrix_ref<T,N>::apply(const Matrix_ref<T, N>& m, F f)                                                  
{                                                                                                             
    // assert matrix sizes                                                                                    
	for(size_type i = desc.start, j = m.desc.start; i != desc.start + desc.size; ++i, ++j)
		f(ptr[i], m.ptr[j]);                                                     
    return *this;                                                                                             
}

template<typename T, size_type N>                                                                             
Matrix_ref<T, N>& Matrix_ref<T, N>::operator+=(const Matrix_ref<T, N>& m)                                                 
{                                                                                                             
    apply(m, [](T& x, const T& y) { x += y; });                                                               
    return *this;                                                                                             
}


template<typename T>
T dot_product(const Matrix_ref<T, 1>& v1, const Matrix_ref<T, 1>& v2)
{
	// assert
	return std::inner_product(v1.cbegin(), v1.cend(), v2.cbegin(), 0.);
}

template<typename T>                                                                                          
Matrix<T, 2> scale_and_add(const Matrix_ref<T, 2>& a, const T& c, const Matrix_ref<T, 2>& b)                          
{                                                                                                             
    Matrix<T, 2> res(a.extent(0), a.extent(1));                                                                               
    for(size_type i= 0; i!=res.size(); ++i)
		*(res.begin()+i) = *(a.begin()+i) * c + *(b.begin()+i);
	return res;
}

template<typename T>                                                                                          
Matrix<T, 1> scale_and_add(const Matrix_ref<T, 1>& a, const T& c, const Matrix_ref<T, 1>& b)                          
{                                                                                                             
    Matrix<T, 1> res(a.size());                                                                               
    for(size_type i= 0; i!=res.size(); ++i)
		res(i) = a(i) * c + b(i);  // *(res.begin()+i) = *(a.begin()+i) * c + *(b.begin()+i);
	return res;
} 



/*
template<typename T, size_type N>
Matrix<T, N> operator+(const Matrix_ref<T, N>& m1, const Matrix_ref<T, N>& m2)
{
	Matrix<T, N> res = m1;
	res += m2;
	return res;
}

                                                                                                           
//    multiply                                                                                                
template<typename T>                                                                                          
Matrix<T, 2> operator*(const Matrix_ref<T, 1>& v1, const Matrix_ref<T, 1>& v2)                                        
{
	const size_type n1 = v1.extent(0);
	const size_type n2 = v2.extent(0);

	assert(1==0);  // indexing will be wrong
	Matrix<T, 2> res(n1, n2);
	for(size_type i=0; i!=n1; ++i)
		for(size_type j=0; j!=n2; ++j)
			res(i, j) = v1(i) * v2(j);
	return res;                                                                                               
}

template<typename T>
Matrix<T, 1> operator*(const Matrix_ref<T, 2>& m, const Matrix_ref<T, 1>& v)
{
	const size_type nr = m.extent(0);
	const size_type nc = m.extent(1);

	assert(1==0);  // indexing will be wrong
	Matrix<T, 1> res(nr);
	for(size_type i=0; i!=nr; ++i)
		for(size_type j=0; j!=nc; ++j)
			res(i) += m(i, j) * v(j);
	return res;                                                                                               
}                                                                                                             
                 
                                                                                                       
template<typename T>                                                                                          
Matrix<T, 2> operator*(const Matrix_ref<T, 2>& m1, const Matrix_ref<T, 2>& m2)                                        
{
	const size_type nr = m1.extent(0);
	const size_type nc = m1.extent(1);                                                                        
    // assert
	const size_type np = m2.extent(1);

	assert(1==0);  // indexing will be wrong
	Matrix<T, 2> res(nr, np);
	for(size_type i=0; i!=nr; ++i)
		for(size_type j=0; j!=np; ++j)
			for(size_type k=0; k!=nc; ++k)
				res(i, j) += m1(i, k) * m2(k, j);
	return res;                                                                                               
}                                                                                                             
*/


