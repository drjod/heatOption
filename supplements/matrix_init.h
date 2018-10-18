#ifndef MATRIX_INIT_H
#define MATRIX_INIT_H

#include <initializer_list>
#include <array>
#include "matrixSlice.h"

using size_type = long;

template<typename T, size_type N> struct Matrix_init
{
	using type = std::initializer_list<typename Matrix_init<T, N-1>::type>;
};


template<typename T> struct Matrix_init<T, 1>
{
	using type = std::initializer_list<T>;
};


/////
 

template<size_type N, typename I, typename List>
typename std::enable_if<(N==1), void>::type
add_extents(I& first, const List& list)
{
	*first++ = list.size();
}

template<size_type N, typename I, typename List>
typename std::enable_if<(N>1), void>::type
add_extents(I& first, const List& list)
{
	*first++ = list.size();
	add_extents<N-1>(first, *list.begin());
}




template<size_type N, typename List>
std::array<size_type, N> derive_extents(const List& list)
{
	std::array<size_type, N> a;
	auto f = a.begin();
	add_extents<N>(f, list);
	//std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
	return a;
}

/////

template<size_type N>
void compute_strides(Matrix_slice<N>& ms)
{
	size_type st = 1;
	for(size_type i=N-1; i>=0; --i)
	{
		ms.strides[i] = st;
		st *= ms.extents[i];	
	}
	ms.size = st;
	ms.start = 0; // ????? added
}


/////


template<typename T, typename Vec>
void add_list(const T* first, const T* last, Vec& vec)
{
	vec.insert(vec.end(), first, last);
}


template<typename T, typename Vec>
void add_list(const std::initializer_list<T>* first, const std::initializer_list<T>* last, Vec& vec)
{
	for(; first != last; ++first)
		add_list(first->begin(), first->end(), vec);
}



template<typename T, typename Vec>
void insert_flat(std::initializer_list<T> list, Vec& vec)
{
	add_list(list.begin(), list.end(), vec);
}


#endif
