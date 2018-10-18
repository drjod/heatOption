// 2D matrix
template<class T> class Matrix<T,2> : public Matrix_base<T>, public Matrix_math<Matrix<T, 2>, T>
{
    const size_type d1;
    const size_type d2;

protected:
    // for use by Row:
    Matrix(size_type n1, size_type n2, T* p) : Matrix_base<T>(n1*n2,p), d1(n1), d2(n2) 
    {
        // std::cerr << "construct 3D Matrix from data\n";
    }

public:
	static const size_type order = 2;

    Matrix(size_type n1, size_type n2) : Matrix_base<T>(n1*n2), d1(n1), d2(n2) { }

    Matrix(Row<T,2>& a) : Matrix_base<T>(a.dim1()*a.dim2(),a.p), d1(a.dim1()), d2(a.dim2())
    { 
        // std::cerr << "construct 2D Matrix from Row\n";
    }
#ifdef CPP11
	// initializer list
	Matrix(std::initializer_list<std::initializer_list<T> > nested_list) :
			Matrix_base<T>(nested_list.size() * nested_list.begin()->size()), 
			d1(nested_list.size()), d2(nested_list.begin()->size())
	{
		size_type i = 0;
		for(auto it = nested_list.begin(); it != nested_list.end(); ++it)
			for(auto it_elem = it->begin(); it_elem != it->end(); ++it_elem)
				this->elem[i++] = *it_elem;
	}
#endif

    // copy constructor: let the base do the copy:
    Matrix(const Matrix& a) : Matrix_base<T>(a.size(),0), d1(a.d1), d2(a.d2)
    {
        // std::cerr << "copy ctor\n";
        this->base_copy(a);
    }

    template<size_type n1, size_type n2> 
    Matrix(const T (&a)[n1][n2]) : Matrix_base<T>(n1*n2), d1(n1), d2(n2)
        // deduce "n1", "n2" (and "T"), Matrix_base allocates T[n1*n2]
    {
        // std::cerr << "matrix ctor\n";
		LOG("Matrix 2: Copy elements");
        for (size_type i = 0; i<n1; ++i)
            for (size_type j = 0; j<n2; ++j) this->elem[i*n2+j]=a[i][j];
    }

    template<class F> Matrix(const Matrix& a, F f) : Matrix_base<T>(a.size()), d1(a.d1), d2(a.d2)
        // construct a new Matrix with element's that are functions of a's elements:
        // does not modify a unless f has been specifically programmed to modify its argument
        // T f(const T&) would be a typical type for f
    {
		LOG("Matrix 2: Apply unary function to elements");
        for (size_type i = 0; i<this->sz; ++i) this->elem[i] = f(a.elem[i]); 
    }

    template<class F, class Arg> Matrix(const Matrix& a, F f, const Arg& t1) : Matrix_base<T>(a.size()), d1(a.d1), d2(a.d2)
        // construct a new Matrix with element's that are functions of a's elements:
        // does not modify a unless f has been specifically programmed to modify its argument
        // T f(const T&, const Arg&) would be a typical type for f
    {
		LOG("Matrix 2: Apply binary function to elements");
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
        // std::cerr << "copy assignment (" << this->size() << ',' << a.size()<< ")\n";
        if (d1!=a.d1 || d2!=a.d2) error("length error in 2D =");
        this->base_assign(a);
        return *this;
    }

    Matrix& operator=(const T& c)  { this->base_apply(Assign<T>(),c);       return *this; }

    ~Matrix() { }
    
    size_type dim1() const { return d1; }    // number of elements in a row
    size_type dim2() const { return d2; }    // number of elements in a column

    Matrix xfer()   // make an Matrix to move elements out of a scope
    {
        Matrix x(dim1(),dim2(),this->data()); // make a descriptor
        this->base_xfer(x);            // transfer (temporary) ownership to x
        return x;
    }

    void range_check(size_type n1, size_type n2) const
    {
        // std::cerr << "range check: (" << d1 << "," << d2 << "): " << n1 << " " << n2 << "\n";
        if (n1<0 || d1<=n1) error("2D range error: dimension 1");
        if (n2<0 || d2<=n2) error("2D range error: dimension 2");
    }

    // subscripting:
          T& operator()(size_type n1, size_type n2)       { range_check(n1,n2); return this->elem[n1*d2+n2]; }
    const T& operator()(size_type n1, size_type n2) const { range_check(n1,n2); return this->elem[n1*d2+n2]; }

    // slicing (return a row):
          Row<T,1> operator[](size_type n)       { return row(n); }
    const Row<T,1> operator[](size_type n) const { return row(n); }

          Row<T,1> row(size_type n)       { range_check(n,0); return Row<T,1>(d2,&this->elem[n*d2]); }
    const Row<T,1> row(size_type n) const { range_check(n,0); return Row<T,1>(d2,&this->elem[n*d2]); }

    Row<T,2> slice(size_type n)
        // rows [n:d1)
    {
        if (n<0) n=0;
        else if(d1<n) n=d1;    // one beyond the end
        return Row<T,2>(d1-n,d2,this->elem+n*d2);
    }

    const Row<T,2> slice(size_type n) const
        // rows [n:d1)
    {
        if (n<0) n=0;
        else if(d1<n) n=d1;    // one beyond the end
        return Row<T,2>(d1-n,d2,this->elem+n*d2);
    }

    Row<T,2> slice(size_type n, size_type m)
        // the rows [n:m)
    {
        if (n<0) n=0;
        if(d1<m) m=d1;    // one beyond the end
        return Row<T,2>(m-n,d2,this->elem+n*d2);

    }

    const Row<T,2> slice(size_type n, size_type m) const
        // the rows [n:sz)
    {
        if (n<0) n=0;
        if(d1<m) m=d1;    // one beyond the end
        return Row<T,2>(m-n,d2,this->elem+n*d2);
    }

    // Column<T,1> column(size_type n); // not (yet) implemented: requies strides and operations on columns
	friend class Matrix_math<Matrix<T, 2>, T>;
};

