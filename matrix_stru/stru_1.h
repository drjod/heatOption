// 1D vector
template<class T> class Matrix<T,1> : public Matrix_base<T> , public Matrix_math<Matrix<T, 1>, T> 
{
    const size_type d1;

protected:
    // for use by Row:
    Matrix(size_type n1, T* p) : Matrix_base<T>(n1,p), d1(n1)
    {
        // std::cerr << "construct 1D Matrix from data\n";
    }

public:
	static const size_type order = 1;

    explicit Matrix(size_type n1) : Matrix_base<T>(n1), d1(n1) { }

    Matrix(Row<T,1>& a) : Matrix_base<T>(a.dim1(),a.elem), d1(a.dim1()) 
    { 
        // std::cerr << "construct 1D Matrix from Row\n";
    }
#ifdef CPP11
	// initializer list
	Matrix(std::initializer_list<T> list) : 
		Matrix_base<T>(list.size()), d1(list.size())
	{
		for(unsigned int i=0u; i!=list.size(); ++i)
			this->elem[i] = *(list.begin() +i); 
	}
#endif
    // copy constructor: let the base do the copy:
    Matrix(const Matrix& a) : Matrix_base<T>(a.size(),0), d1(a.d1)
    {
        // std::cerr << "copy ctor\n";
        this->base_copy(a);
    }

    template<size_type n> 
    Matrix(const T (&a)[n]) : Matrix_base<T>(n), d1(n)
        // deduce "n" (and "T"), Matrix_base allocates T[n]
    {
        // std::cerr << "matrix ctor\n";
		LOG("Matrix 1: Copy elements");
        for (size_type i = 0; i<n; ++i) this->elem[i]=a[i];
    }

    Matrix(const T* p, size_type n) : Matrix_base<T>(n), d1(n)
        // Matrix_base allocates T[n]
    {
        // std::cerr << "matrix ctor\n";
		LOG("Matrix 1: Copy elements");
        for (size_type i = 0; i<n; ++i) this->elem[i]=p[i];
    }

    template<class F> Matrix(const Matrix& a, F f) : Matrix_base<T>(a.size()), d1(a.d1)
        // construct a new Matrix with element's that are functions of a's elements:
        // does not modify a unless f has been specifically programmed to modify its argument
        // T f(const T&) would be a typical type for f
    {
		LOG("Matrix 1: Apply unary function to elements");
        for (size_type i = 0; i<this->sz; ++i) this->elem[i] = f(a.elem[i]); 
    }

    template<class F, class Arg> Matrix(const Matrix& a, F f, const Arg& t1) : Matrix_base<T>(a.size()), d1(a.d1)
        // construct a new Matrix with element's that are functions of a's elements:
        // does not modify a unless f has been specifically programmed to modify its argument
        // T f(const T&, const Arg&) would be a typical type for f
    {
		LOG("Matrix 1: Apply binary function to elements");
        for (size_type i = 0; i<this->sz; ++i) this->elem[i] = f(a.elem[i],t1); 
    }

	const T& element(size_type i) const { return this->elem[i]; }

	template<typename Op1, typename Op2>
	Matrix& operator=(const MatrixAdd<Op1, Op2>& m)
	{
		for(size_type i=0; i < this->size(); ++i)
		{
			this->elem[i] = m.element(i);
		}
		return *this;
	}

	template<typename Op1, typename Op2>
	Matrix& operator=(const MatrixSub<Op1, Op2>& m)
	{
		for(size_type i=0; i < this->size(); ++i)
		{
			this->elem[i] = m.element(i);
		}
		return *this;
	}

    Matrix& operator=(const Matrix& a)
        // copy assignment: let the base do the copy
    {
		LOG("Matrix 1: Assign");
        // std::cerr << "copy assignment (" << this->size() << ',' << a.size()<< ")\n";
        if (d1!=a.d1) error("length error in 1D=");
        this->base_assign(a);
        return *this;
    }

	Matrix& operator=(const T& c)  { this->base_apply(Assign<T>(),c); return *this; }

    ~Matrix() { }


    size_type dim1() const { return d1; }    // number of elements in a row

    Matrix xfer()    // make a Matrix to move elements out of a scope
    {
		LOG("Matrix 1: Xfer");	
        Matrix x(dim1(),this->data()); // make a descriptor
        this->base_xfer(x);                  // transfer (temporary) ownership to x
        return x;
    }

    void range_check(size_type n1) const
    {
        // std::cerr << "range check: (" << d1 << "): " << n1 << "\n"; 
        if (n1<0 || d1<=n1) error("1D range error: dimension 1");
    }

    // subscripting:
          T& operator()(size_type n1)       { range_check(n1); return this->elem[n1]; }
    const T& operator()(size_type n1) const { range_check(n1); return this->elem[n1]; }

    // slicing (the same as subscripting for 1D matrix):
          T& operator[](size_type n)       { return row(n); }
    const T& operator[](size_type n) const { return row(n); }

          T& row(size_type n)       { range_check(n); return this->elem[n]; }
    const T& row(size_type n) const { range_check(n); return this->elem[n]; }

    Row<T,1> slice(size_type n)
        // the last elements from a[n] onwards
    {
        if (n<0) n=0;
        else if(d1<n) n=d1;// one beyond the end
        return Row<T,1>(d1-n,this->elem+n);
    }

    const Row<T,1> slice(size_type n) const
        // the last elements from a[n] onwards
    {
        if (n<0) n=0;
        else if(d1<n) n=d1;// one beyond the end
        return Row<T,1>(d1-n,this->elem+n);
    }

    Row<T,1> slice(size_type n, size_type m)
        // m elements starting with a[n]
    {
        if (n<0) n=0;
        else if(d1<n) n=d1;    // one beyond the end
        if (m<0) m = 0;
        else if (d1<n+m) m=d1-n;
        return Row<T,1>(m,this->elem+n);
    }

    const Row<T,1> slice(size_type n, size_type m) const
        // m elements starting with a[n]
    {
        if (n<0) n=0;
        else if(d1<n) n=d1;    // one beyond the end
        if (m<0) m = 0;
        else if (d1<n+m) m=d1-n;
        return Row<T,1>(m,this->elem+n);
    }

	friend class Matrix_math<Matrix<T, 1 >, T>;
};

