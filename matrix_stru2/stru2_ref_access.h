
template<typename T, size_type N>
template<typename... Args> 
typename std::enable_if<Requesting_element<Args...>(), T&>::type
Matrix_ref<T, N>::operator()(Args... args)
{                                                                                                             
    //return const_cast<T&>(static_cast<const Matrix_ref<T, N>&>(*this)(args...));                                  
    return *(ptr + desc(args...));                                                                         
} 


template<typename T, size_type N>
template<typename... Args> 
typename std::enable_if<Requesting_element<Args...>(), const T&>::type
Matrix_ref<T, N>::operator()(Args... args) const
{                                                                                                             
    // assert                                                                                                 
    return *(ptr + desc(args...));                                                                         
}


template<typename T, size_type N>
template<typename... Args>
typename std::enable_if<Requesting_slice<Args...>(), Matrix_ref<T, N> >::type
Matrix_ref<T, N>::operator()(const Args&... args)
{

    // return const_cast<Matrix_ref<T, N> >(static_cast<const Matrix_ref<T, N>&>(*this)(const args&...));                                  
	Matrix_slice<N> d;
	d.start = do_slice(desc, d, args...);
	return {d, ptr};
}

template<typename T, size_type N>
template<typename... Args> 
typename std::enable_if<Requesting_slice<Args...>(), Matrix_ref<const T, N> >::type
Matrix_ref<T, N>::operator()(const Args&... args) const
{
	Matrix_slice<N> d;
	d.start = do_slice(desc, d, args...);
	return {d, ptr};
}


template<typename T, size_type N>
T& Matrix_ref<T, N>::rowN(size_type i, std::true_type)
{ 
	return ptr[i+desc.start];
}

template<typename T, size_type N>                                                                             
Matrix_ref<T, N-1>  Matrix_ref<T, N>::rowN(size_type n, std::false_type)
{                                                                                                             
    // assert(n<rows());                                                                                      
    Matrix_slice<N-1> row;
    row.start = desc.extents[1]*n;                                                                            
    row.size = desc.extents[1];                                                                               
    row.extents[0] = desc.extents[1];                                                                         
    row.strides[0] = 1;                                                                                       
    // slice_dim<0>(n, desc, row);                                                                            
    return {row, ptr};                                                                                     
}         


template<typename T, size_type N>                                                                             
auto Matrix_ref<T, N>::row(size_type n)                                                                           
{
	typename std::conditional<(N==1), std::true_type, std::false_type>::type N1;
	return rowN(n, N1);
}


template<typename T, size_type N>
const T& Matrix_ref<T, N>::rowN(size_type i, std::true_type) const
{ 
	return ptr[i+desc.start];
}

template<typename T, size_type N>                                                                             
Matrix_ref<const T, N-1>  Matrix_ref<T, N>::rowN(size_type n, std::false_type) const
{
	// assert(n<rows());                                                                                      
    Matrix_slice<N-1> row;

	row.start = desc.extents[1]*n;
	row.size = desc.extents[1];
	row.extents[0] = desc.extents[1];
	row.strides[0] = 1;
	// slice_dim<0>(n, desc, row);
	return {row, ptr};
}

template<typename T, size_type N>                                                                             
const auto Matrix_ref<T, N>::row(size_type n) const 
{
	typename std::conditional<(N==1), std::true_type, std::false_type>::type N1;
	return rowN(n, N1);
}


//template<typename T> class Matrix_ref<T, 1>;
/*
// specializations
template<typename T, size_type N>
typename std::enable_if<(N==1), T&>::type 
Matrix_ref<T, N>::row(size_type i)
{
	return ptr[i];
}*/


