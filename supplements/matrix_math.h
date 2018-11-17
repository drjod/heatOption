#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H

#include <omp.h>
#include <cmath>
                                                                                                           
//    multiplication                                                                                                
template<typename T>                                                                                          
Matrix<T, 2> operator*(const Matrix<T, 1>& v1, const Matrix<T, 1>& v2)                                        
{                                                                                                             
    const size_type n1 = v1.dim1();                                                                        
    const size_type n2 = v2.dim1();                                                                        
                                                                                                              
    Matrix<T, 2> res(n1, n2);                                                                                 
    for(size_type i=0; i!=n1; ++i)                                                                            
        for(size_type j=0; j!=n2; ++j)                                                                        
            res(i, j) = v1(i) * v2(j);                                                                        
    return res;                                                                                               
}                                                                                                             
                                                                                                              



template<typename T>                                                                                          
Matrix<T, 1> operator*(const Matrix<T, 2>& m, const Matrix<T, 1>& v)                                          
{                                                                                                             
    const size_type nr = m.dim1();                                                                         
    const size_type nc = m.dim2();                                                                         
    Matrix<T, 1> res(nr);                                                                                     
    for(size_type i=0; i!=nr; ++i)                                                                            
        for(size_type j=0; j!=nc; ++j)                                                                        
            res(i) += m(i, j) * v(j);                                                                         
    return res;                                                                                               
}                                                                                                             
                 
                                                                                                       
template<typename T>                                                                                          
Matrix<T, 2> operator*(const Matrix<T, 2>& m1, const Matrix<T, 2>& m2)                                        
{                                                                                                             
    const size_type nr = m1.dim1();                                                                        
    const size_type nc = m1.dim2();                                                                        
    // assert                                                                                                 
    const size_type np = m2.dim2();                                                                        
     
    Matrix<T, 2> res(nr, np);                                                                                 
    for(size_type i=0; i!=nr; ++i)                                                                            
        for(size_type j=0; j!=np; ++j)                                                                        
            for(size_type k=0; k!=nc; ++k)                                                                    
                res(i, j) += m1(i, k) * m2(k, j);                                                             
	return res;
}                                                                                                             
                                                                                                              
// -------------------------------------------------------------------------------------------

template<typename T>                                                                                          
T dot_product(const Matrix<T, 1>& v1, const Matrix<T, 1>& v2)                                                 
{ 

	//if (v1.size() != v2.size()) error("sizes wrong for dot product");
    T sum = 0;
    for (size_type i = 0; i<v1.size(); ++i) 
		sum += v1(i) * v2(i);
    
	return sum;
}                                                                                                             

// -------------------------------------------------------------------------------------------
                    
template<typename T>
Matrix<T, 1> scale_and_add(const Matrix<T, 1>& a, const T& c, const Matrix<T, 1>& b)
{
	Matrix<T, 1> res(a.size());
	for(size_type i=0; i!=a.size(); ++i)
		res(i) = a(i) * c + b(i);
	return res;
}


/*
template<typename T, size_type N>
Matrix<T, N> operator+(const Matrix<T, N>& m1, const Matrix<T, N>& m2)
{
	Matrix<T, N> res = m1;
	res += m2;
	return res;
}

template<typename T, size_type N>
Matrix<T, N> operator-(const Matrix<T, N>& m1, const Matrix<T, N>& m2)
{
	Matrix<T, N> res = m1;
	res -= m2;
	return res;
}
*/

// -------------------------------------------------------------------------------------------


template<typename T>                                                                                          
Matrix<T, 1> matrix_multiply(const Matrix<T, 2>& m, const Matrix<T, 1>& v)                                          
{                                                                                                             
    const size_type nr = m.dim1();                                                                         
    const size_type nc = m.dim2();                                                                         
    Matrix<T, 1> res(nr);                                                                                     

	#pragma omp parallel num_threads(1)
	{
		int n = omp_get_thread_num();
		int t = omp_get_num_threads();		
		int bs = 256;  // block size
		Matrix<T, 1> res_local(nr);
		
		//for(size_type i=0; i<nr; ++i)                                                                            
		//	for(size_type k=n; k<std::ceil(double(nc)/bs); k+=t)
		//		for(size_type j=k*bs; j<(k+1)*bs && j<nc; j+=1)                                                                        
		//for(size_type k=n; k<std::ceil(double(nr)/bs); k+=t)
		//	for(size_type i=k*bs; i<(k+1)*bs && i<nr; i+=1)																
			#pragma omp for schedule(static, 512)
			for(size_type i=0; i<nr; ++i)                                                                            
				for(size_type j=0; j<nc; ++j)                                                                            
				{
					res_local(i) += m(i, j) * v(j);
				}

		#pragma omp critical
		res += res_local;                                                               
	}
    return res;                                                                                               
}                                                                                                             
                 

#endif
