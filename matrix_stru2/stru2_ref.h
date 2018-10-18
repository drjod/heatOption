

template<typename T, size_type N>                                                                                       
class Matrix_ref                                                                                              
{                                                                                                             
public:
	static constexpr size_type order = N;

	// construct
	Matrix_ref(const Matrix_slice<N>& s, T* _ptr) : desc(s), ptr(_ptr) {}
	template<typename... Exts> explicit Matrix_ref(Exts... exts);

	//template<typename T2>
	//Matrix_ref(const Matrix_ref<T2, N>& m)
	Matrix_ref(const Matrix_ref& m) 
: desc(m.descriptor()), ptr(m.ptr)
	{
//ptr+=3;
//desc.start+=3;
//std::cout << desc << '\n';
//std::cout << m.desc << '\n';
		std::cout << "COPY NOT CHECKED\n";
		//for(size_type i=0; i != m.desc.size; ++i)
		//	ptr[i+desc.start] = m.ptr[i+m.desc.start];	
	}

	Matrix_ref(Matrix<T, N>& m) : desc(m.descriptor()), ptr(m.data()) {}


	Matrix_ref& operator=(const Matrix<T, N>& m) 
	{ 
		for(size_type i=0; i != m.size(); ++i)
			ptr[i+desc.start] = m(i);	
		desc=m.descriptor(); 
		return *this;
	}

	// assign
	template<typename T2>
	Matrix_ref& operator=(const Matrix_ref<T2, N>& m) 
	//Matrix_ref& operator=(const Matrix_ref& m) 
	{ 
		for(size_type i=0; i != m.descriptor().size; ++i)
			ptr[i+descriptor().start] = m.data()[i+m.descriptor().start];	
		desc=m.descriptor(); 
		return *this;
	}

	//operator Matrix<T, N>() const { return Matrix<T, N>(); }

	// access
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

	T& rowN(size_type n, std::true_type);
	const T& rowN(size_type n, std::true_type) const;
	Matrix_ref<T, N-1> rowN(size_type n, std::false_type);
	Matrix_ref<const T, N-1> rowN(size_type n, std::false_type) const;

	auto row(size_type n);
	const auto row(size_type n) const;

	Matrix_ref<T, N-1> operator[](size_type i) { return row(i); }
	Matrix_ref<const T, N-1> operator[](size_type i) const { return row(i); }

	//T& operator[](size_type i) { return row(i); }
	//const T& operator[](size_type i) const { return row(i); }
	
    // slice access                                                                                           
    size_type extent(size_type n) const { return desc.extents[n]; }                                           
    size_type size() const { return desc.size; }                                                           
    const Matrix_slice<N>& descriptor() const { return desc; }  

	// math operations
	template<typename F> Matrix_ref& apply(F f);	
	template<typename F> Matrix_ref& apply(const Matrix_ref& m, F f);
	Matrix_ref& operator+=(const Matrix_ref& m);

	template<typename T2>
	friend T2 dot_product(const Matrix<T2, 1>& v1, const Matrix<T2, 1>& v2);

	template<typename T2, size_type N2>
	friend std::ostream& operator<<(std::ostream& os, const Matrix_ref<T2, N2>& m);

	T* begin() const { return ptr + desc.start; }
	T* end() const { return ptr + desc.start + desc.size; }

	const T* cbegin() const { return ptr + desc.start; }
	const T* cend() const { return ptr + desc.start + desc.size; }
	T* data() { return ptr; }
	const T* data() const { return ptr; }

private:                                                                                                      
    Matrix_slice<N> desc;                                                                                     
    T* ptr;                                                                                                   
};


template<typename T>
class Matrix_ref<T, 0>
{
public:
	static constexpr size_type order = 0;
	using value_type = T;

	Matrix_ref(const T& _elem) : elem(_elem) {}
	Matrix_ref& operator=(const T& value) { elem = value; return *this; }

	Matrix_ref(const Matrix_slice<0>& s, T* _ptr) : elem(*_ptr) {}

	T& operator()() { return elem; } 
	const T& operator()() const { return elem; } 

	operator T&() { return elem; }
	operator const T&() const { return elem; }
private:
	T elem;
};


// construct
template<typename T, size_type N>                                                                             
template<typename... Exts>                                                                                    
Matrix_ref<T, N>::Matrix_ref(Exts... exts) : desc{exts...}//, elems(desc.size)                                          
{}    

#include "stru2_ref_access.h"
#include "stru2_ref_math.h"
