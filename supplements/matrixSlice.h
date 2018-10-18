#ifndef MATRIX_SLICE_H
#define MATRIX_SLICE_H

#include <array>
#include <initializer_list>
#include <numeric>

using size_type = long;

template<size_type N> struct Matrix_slice                                                                                           
{                                                                                                             
    Matrix_slice() = default;                                                                                 
    Matrix_slice(size_type offset, std::initializer_list<size_type> exts);                                
    Matrix_slice(size_type offset, std::initializer_list<size_type> exts,                                 
                                        std::initializer_list<size_type> strs);                             
                                                                                                              
    template<typename... Dims> Matrix_slice(Dims... dims);                                                    
    template<typename... Dims> size_type operator()(Dims... dims) const;  // calculate index                
                                                                                                              
    size_type start;                                                                                        
    size_type size;                                                                                         
    std::array<size_type, N> extents;                                                                       
    std::array<size_type, N> strides;                                                                       
                                                                                                              
};                                                                                                            

/*
template<size_type N>
std::ostream& operator<<(std::ostream& os, const Matrix_slice<N>& m)
{
	os << "start: " << m.start << '\n';
	os << "size: " << m.size << '\n';

	os << "extents: ";
	std::copy(m.extents.begin(), m.extents.end(), std::ostream_iterator<int>(os, " "));
	os << '\n';

	os << "strides: ";
	std::copy(m.strides.begin(), m.strides.end(), std::ostream_iterator<int>(os, " "));
	os << '\n';

	return os;
}
*/

template<size_type N>
Matrix_slice<N>::Matrix_slice(size_type offset, std::initializer_list<size_type> exts)                                
{
	start = offset;
	size_type i = 0;
	for(auto it = exts.begin(); it!= exts.end(); ++it)
		extents[i++] = *it;
}

template<size_type N>
template<typename... Dims>
Matrix_slice<N>::Matrix_slice(Dims... dims) : start(0)
{
	size_type args[N] {size_type(dims)...};

	for(int i=0; i<N; ++i)
	{
		strides[i] = 1;
		extents[i] = args[i];
	}

	size = args[N-1];
	strides[N-1] = 1;
	for(int i=N-2; i>=0; --i)
	{
		strides[i] = extents[i+1]*strides[i+1];
		size *= extents[i];
	}
}
                                                                                                              
template<size_type N>
Matrix_slice<N>::Matrix_slice(size_type offset, std::initializer_list<size_type> exts, 
								std::initializer_list<size_type> strs)                                
{
	start = offset;
	size_type i = 0;
	for(auto it = exts.begin(); it!= exts.end(); ++it)
		extents[i++] = *it;
	i = 0;
	for(auto it = strs.begin(); it!= strs.end(); ++it)
		strides[i++] = *it;
}

template<size_type N>                                                                                       
template<typename... Dims>                                                                                    
size_type Matrix_slice<N>::operator()(Dims... dims) const                                                   
{                                                                                                           
    static_assert(sizeof...(Dims) == N, "Matrix_slice<N>::operator(): Dimension mismatch");                   
    size_type args[N] { size_type(dims)... };                                                             
    return start + std::inner_product(args, args+N, strides.begin(), size_type{0});                         
} 

                                                                                                            

// for efficiency
/*                                                                                                        
template<>                                                                                                    
struct Matrix_slice<1>                                                                                        
{ 
	// ...                                                                                                            
    size_type operator()(size_type i) const { return i; }                                                 
};                                                                                                            
                                                                                                              
template<>                                                                                                    
struct Matrix_slice<2>                                                                                        
{         
	// ...                                                                                                    
    size_type start;                                                                                        
    std::array<size_type, 2> strides;                                                                       
    size_type operator()(size_type i, size_type j) const { return start + i*strides[0] + j; }           
};
*/                                                                                                            

#endif
