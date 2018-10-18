
template<typename T, size_type N>
template<typename... Args> 
typename std::enable_if<Requesting_element<Args...>(), T&>::type
Matrix<T, N>::operator()(Args... args)
{                                                                                                             
	return *(data() + desc(args...));
    //return const_cast<T&>(static_cast<const Matrix<T, N>&>(*this)(args...));                                  
} 


template<typename T, size_type N>
template<typename... Args> 
typename std::enable_if<Requesting_element<Args...>(), const T&>::type
Matrix<T, N>::operator()(Args... args) const
{
	// assert
	return *(data() + desc(args...));
}


template<typename T, size_type N>
template<typename... Args>
typename std::enable_if<Requesting_slice<Args...>(), Matrix_ref<T, N> >::type
Matrix<T, N>::operator()(const Args&... args)
{

    // return const_cast<Matrix_ref<T, N> >(static_cast<const Matrix<T, N>&>(*this)(const args&...));                                  
	Matrix_slice<N> d;
	d.start = do_slice(desc, d, args...);
	/*d.extents[0] = 223;
	d.extents[1] = 223;
	d.strides[0]=223;
	d.strides[1]=221;
*/
	//d.strides[1]=1;
	return {d, data()};
}

template<typename T, size_type N>
template<typename... Args> 
typename std::enable_if<Requesting_slice<Args...>(), Matrix_ref<const T, N> >::type
Matrix<T, N>::operator()(const Args&... args) const
{
	Matrix_slice<N> d;
	d.start = do_slice(desc, d, args...);
	return {d, data()};
}

template<typename T, size_type N>
T& Matrix<T, N>::rowN(size_type n, std::true_type)
{
	return elems.data()[n+desc.start];
}

template<typename T, size_type N>
Matrix_ref<T, N-1> Matrix<T, N>::rowN(size_type n, std::false_type)
{
	// assert(n<rows());
	Matrix_slice<N-1> row;
	row.start = desc.extents[1]*n;
	row.size = desc.extents[1];
	row.extents[0] = desc.extents[1];
	row.strides[0] = 1;
	//slice_dim<0>(n, desc, row);
	return {row, data()};
}

template<typename T, size_type N>
auto Matrix<T, N>::row(size_type n)
{
	typename std::conditional<(N==1), std::true_type, std::false_type>::type N1;
	return rowN(n, N1);
}

template<typename T, size_type N>
const T& Matrix<T, N>::rowN(size_type n, std::true_type) const
{
	return elems.data()[n+desc.start];
}

template<typename T, size_type N>
Matrix_ref<const T, N-1> Matrix<T, N>::rowN(size_type n, std::false_type) const
{
	// assert(n<rows());
	Matrix_slice<N-1> row;
	row.start = desc.extents[1]*n;
	row.size = desc.extents[1];
	row.extents[0] = desc.extents[1];
	row.strides[0] = 1;
	// slice_dim<0>(n, desc, row);
	return {row, data()};
}

template<typename T, size_type N>
const auto Matrix<T, N>::row(size_type n) const
{
	typename std::conditional<(N==1), std::true_type, std::false_type>::type N1;
	return rowN(n, N1);
}
