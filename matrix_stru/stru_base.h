// Matrix_base represents the common part of the Matrix classes:
template<class T> class Matrix_base {
    // matrixs store their memory (elements) in Matrix_base and have copy semantics
    // Matrix_base does element-wise operations
public:
	typedef T value_type;
protected:
    T* elem;    // vector? no: we couldn't easily provide a vector for a slice
    const size_type sz;    
    mutable bool owns;
    mutable bool xfer;

    Matrix_base(size_type n) :elem(new T[n]()), sz(n), owns(true), xfer(false)
        // matrix of n elements (default initialized)
    {
		LOG("Base: Construct (owns)");
        // std::cerr << "new[" << n << "]->" << elem << "\n";
    }

    Matrix_base(size_type n, T* p) :elem(p), sz(n), owns(false), xfer(false)
        // descriptor for matrix of n elements owned by someone else
    {
		LOG("Base: Construct (owns not)");
    }

    ~Matrix_base()
    {
        if (owns) {
			LOG("Base: Delete");
            // std::cerr << "delete[" << sz << "] " << elem << "\n";
            delete[]elem;
        }
    }

    void copy_elements(const Matrix_base& a)
    {
		LOG("Base: Copy elements");
        if (sz!=a.sz) error("copy_elements()");
        for (size_type i=0; i<sz; ++i) elem[i] = a.elem[i];
    }

    void base_assign(const Matrix_base& a) 
	{
		LOG("Base: Assign");
		//base_copy(a);
		copy_elements(a); 
	}

    void base_copy(const Matrix_base& a)
    {
        if (a.xfer) {          // a is just about to be deleted
                               // so we can transfer ownership rather than copy
            // std::cerr << "xfer @" << a.elem << " [" << a.sz << "]\n";
            elem = a.elem;
            a.xfer = false;    // note: modifies source
            a.owns = false;
        }
        else {
            elem = new T[a.sz];
            // std::cerr << "base copy @" << a.elem << " [" << a.sz << "]\n";
            copy_elements(a);
        }
        owns = true;
        xfer = false;
    }

    // to get the elements of a local matrix out of a function without copying:
    void base_xfer(Matrix_base& x) //const
    {
		LOG("Base: Xfer");
        if (owns==false) error("cannot xfer() non-owner");
        owns = false;     // now the elements are safe from deletion by original owner
        x.xfer = true;    // target asserts temporary ownership
        x.owns = true;
    }

    template<class F> void base_apply(F f) 
	{ LOG("Base: Apply unary function"); for (size_type i = 0; i<size(); ++i) f(elem[i]); }
    template<class F> void base_apply(F f, const T& c) 
	{ LOG("Base: Apply binary function"); for (size_type i = 0; i<size(); ++i) f(elem[i],c); }
public:
    // if necessay, we can get to the raw matrix:
          T* data()       { return elem; }
    const T* data() const { return elem; }
    size_type    size() const { return sz; }

private:
    void operator=(const Matrix_base&);    // no ordinary copy of bases
    Matrix_base(const Matrix_base&);
};

