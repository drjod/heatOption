
// math operations                                                                                            
//    add                                                                                                     
template<typename T, size_type N>                                                                             
template<typename F>                                                                                          
Matrix<T, N>& Matrix<T, N>::apply(F f)                                                                        
{                                                                                                             
    for(auto& x : elems) f(x);                                                                                
    return *this;                                                                                             
}                                                                                                             
                                                                                                              
template<typename T, size_type N>                                                                             
template<typename F>                                                                                          
Matrix<T, N>& Matrix<T,N>::apply(const Matrix<T, N>& m, F f)                                                  
{                                                                                                             
    // assert matrix sizes                                                                                    
    for(auto it = elems.begin(), it_m = m.elems.begin(); it != elems.end(); ++it, ++it_m)  // iterators in matrix     
        f(*it, *it_m);                                                                                        
    return *this;                                                                                             
}                                                                                                             
                                                                                                              
// addition
template<typename T, size_type N>                                                                             
Matrix<T, N>& Matrix<T, N>::operator+=(const Matrix<T, N>& m)                                                 
{                                                                                                             
    apply(m, [](T& x, const T& y) { x += y; });                                                               
    return *this;                                                                                             
}
// subtraction
template<typename T, size_type N>                                                                             
Matrix<T, N>& Matrix<T, N>::operator-=(const Matrix<T, N>& m)                                                 
{                                                                                                             
    apply(m, [](T& x, const T& y) { x -= y; });                                                               
    return *this;                                                                                             
}


/////////////////////
// nonmember
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

                                                                                                           
//    multiplication                                                                                                
template<typename T>                                                                                          
Matrix<T, 2> operator*(const Matrix<T, 1>& v1, const Matrix<T, 1>& v2)                                        
{                                                                                                             
    const size_type n1 = v1.extent(0);                                                                        
    const size_type n2 = v2.extent(0);                                                                        
                                                                                                              
    Matrix<T, 2> res(n1, n2);                                                                                 
    for(size_type i=0; i!=n1; ++i)                                                                            
        for(size_type j=0; j!=n2; ++j)                                                                        
            res(i, j) = v1(i) * v2(j);                                                                        
    return res;                                                                                               
}                                                                                                             
                                                                                                              
template<typename T>                                                                                          
Matrix<T, 1> operator*(const Matrix<T, 2>& m, const Matrix<T, 1>& v)                                          
{                                                                                                             
    const size_type nr = m.extent(0);                                                                         
    const size_type nc = m.extent(1);                                                                         
                                                                                                              
    Matrix<T, 1> res(nr);                                                                                     
    for(size_type i=0; i!=nr; ++i)                                                                            
        for(size_type j=0; j!=nc; ++j)                                                                        
            res(i) += m(i, j) * v(j);                                                                         
    return res;                                                                                               
}                                                                                                             
                 
                                                                                                       
template<typename T>                                                                                          
Matrix<T, 2> operator*(const Matrix<T, 2>& m1, const Matrix<T, 2>& m2)                                        
{                                                                                                             
    const size_type nr = m1.extent(0);                                                                        
    const size_type nc = m1.extent(1);                                                                        
    // assert                                                                                                 
    const size_type np = m2.extent(1);                                                                        
                                                                                                              
    Matrix<T, 2> res(nr, np);                                                                                 
    for(size_type i=0; i!=nr; ++i)                                                                            
        for(size_type j=0; j!=np; ++j)                                                                        
            for(size_type k=0; k!=nc; ++k)                                                                    
                res(i, j) += m1(i, k) * m2(k, j);                                                             
    return res;                                                                                               
}                                                                                                             
                                                                                                              
template<typename T>                                                                                          
T dot_product(const Matrix<T, 1>& v1, const Matrix<T, 1>& v2)                                                 
{                                                                                                             
    // assert?                                                                                                
    return std::inner_product(v1.elems.cbegin(), v1.elems.cend(), v2.elems.cbegin(), 0.);                        
}                                                                                                             
                    
template<typename T>
Matrix<T, 1> scale_and_add(const Matrix<T, 1>& a, const T& c, const Matrix<T, 1>& b)
{
	Matrix<T, 1> res(a.size());
	for(size_type i=0; i!=a.size(); ++i)
		res(i) = a(i) * c + b(i);
	return res;
}

*/
