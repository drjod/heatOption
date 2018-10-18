#ifndef SLICE_H
#define SLICE_H

using size_type = long;

#include "matrixSlice.h"

struct slice                                                                                                  
{                                                                                                             
    slice() : start(0), length(0), stride(1) {}                                                               
    explicit slice(size_type _start) : start(_start), length(0), stride(1) {}                              
    slice(size_type _start, size_type _length, size_type _stride=1) :                                   
        start(_start), length(_length), stride(_stride) {}                                                    

	size_type operator()(size_type i) const { return start + i * stride; }                                                                                                              
    size_type start;                                                                                        
    size_type length;                                                                                       
    size_type stride;

};

/*                                                                                                    
std::ostream& operator<<(std::ostream& os, const slice& s)
{
	os << "start: " << s.start << '\n';
	os << "length: " << s.length << '\n';
	os << "stride: " << s.stride << '\n';

	return os;
}
*/


template<size_type M, size_type N>
size_type do_slice_dim(const Matrix_slice<N>& os, Matrix_slice<N>& ns, slice s)
{
	ns.size = s.length;
	ns.extents[0] = s.length;
	ns.strides[0] = os.strides[0];
	return s.start + os.start;
}

template<size_type M, size_type N>
size_type do_slice_dim(const Matrix_slice<N>& os, Matrix_slice<N>& ns, size_type s)
{
	return os.extents[M-1] * s;
}


template<size_type N, typename T, typename... Args>
size_type do_slice(const Matrix_slice<N>& os, Matrix_slice<N>& ns, const T& s, const Args&... args)
{
	size_type m = do_slice_dim<sizeof...(Args)+1>(os, ns, s);
	size_type n = do_slice(os, ns, args...);
	return m+n;
}

template<size_type N>
size_type do_slice(const Matrix_slice<N>& os, Matrix_slice<N>& ns)
{
	return 0;
}
  
#endif
