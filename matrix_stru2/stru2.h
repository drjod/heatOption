#ifndef STRU2_MATRIX_H
#define STRU2_MATRIX_H

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>  // for min_ / max_elenent
#include <numeric>
#include <type_traits>

#include "slice.h"
#include "matrix_init.h"

using size_type = long;

namespace stru2
{

template<typename T, size_type N> class Matrix;
 
using DVec = Matrix<double, 1>;
using DMat = Matrix<double, 2>;
using DTen = Matrix<double, 3>;

#include "stru2_meta.h"
#include "stru2_ref.h"

template<typename T, size_type N> 
using Matrix_initializer = typename Matrix_init<T, N>::type; 


template<typename T, size_type N> class Matrix 
{
public:

	static constexpr size_type order = N;
	// using value_type = T;
	// using iterator = typename std::vector<T>::iterator;
	// using const_iterator = typename std::vector<T>::const_iterator;

	Matrix() = default;
	Matrix(const Matrix&) = default;
	Matrix(Matrix&&) = default;
	Matrix& operator=(const Matrix&) = default;
	Matrix& operator=(Matrix&&) = default;
	~Matrix() = default;

	// construct
	template<typename... Exts> explicit Matrix(Exts... exts);

	Matrix(Matrix_initializer<T, N>);
	Matrix& operator=(Matrix_initializer<T, N>);

	template<typename T2> Matrix(const Matrix_ref<T2, N>&);
	//template<typename T2> Matrix(std::initializer_list<T2>) = delete;

	// assign
	template<typename T2> Matrix& operator=(const Matrix_ref<T2, N>&);
	//template<typename T2> Matrix& operator=(std::initializer_list<T2>) = delete;

	//access
	template<typename... Args> 
	typename std::enable_if<Requesting_element<Args...>(), T&>::type
	operator()(Args... args);

	template<typename... Args> 
	typename std::enable_if<Requesting_element<Args...>(), const T&>::type
	operator()(Args... args) const;

	template<typename... Args>
	typename std::enable_if<Requesting_slice<Args...>(), Matrix_ref<T, N> >::type
	operator()(const Args&... args);

	template<typename... Args> 
	typename std::enable_if<Requesting_slice<Args...>(), Matrix_ref<const T, N> >::type
	operator()(const Args&... args) const;

	// required here???
	T& rowN(size_type n, std::true_type);
	const T& rowN(size_type n, std::true_type) const;
	Matrix_ref<T, N-1> rowN(size_type n, std::false_type);
	Matrix_ref<const T, N-1> rowN(size_type n, std::false_type) const;

	auto row(size_type n);
	const auto row(size_type n) const;

	Matrix_ref<T, N-1> operator[](size_type i) { return row(i); }
	Matrix_ref<const T, N-1> operator[](size_type i) const { return row(i); }

	T* data() { return elems.data(); }
	const T* data() const { return elems.data(); }
	
	T max() const { return *std::max_element(elems.begin(), elems.end()); }
	T min() const { return *std::min_element(elems.begin(), elems.end()); }

	// slice access
	size_type extent(size_type n) const { return desc.extents[n]; }
	size_type size() const { return elems.size(); }
	const Matrix_slice<N>& descriptor() const { return desc; }

	size_type dim1() const { return extent(0); }
	size_type dim2() const { return extent(1); }
	size_type dim3() const { return extent(2); }

	// math operations
	template<typename F> Matrix& apply(F f);	
	template<typename F> Matrix& apply(const Matrix& m, F f);
	Matrix& operator+=(const Matrix& m);
	Matrix& operator-=(const Matrix& m);

	/*template<typename T2>
	friend T2 dot_product(const Matrix<T2, 1>& v1, const Matrix<T2, 1>& v2);

	template<typename T2, size_type N2>
	friend std::ostream& operator<<(std::ostream& os, const Matrix<T2, N2> m);
*/
private:
	Matrix_slice<N> desc;
	std::vector<T> elems;

};


template<typename T>
class Matrix<T, 0>
{
public:
	static constexpr size_type order = 0;
	using value_type = T;

	Matrix(const T& _elem) : elem(_elem) {}
	Matrix& operator=(const T& value) { elem = value; return *this; }

	T& operator()() { return elem; } 
	const T& operator()() const { return elem; } 

	operator T&() { return elem; }
	operator const T&() const { return elem; }
private:
	T elem;
};

#include "stru2_construct.h"
#include "stru2_access.h"
#include "stru2_math.h"


}  // end namespace

#endif
