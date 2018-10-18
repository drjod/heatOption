//-----------------------------------------------------------------------------

template<class T> class Row<T,1> : public Matrix<T,1> {
public:
    Row(size_type n, T* p) : Matrix<T,1>(n,p)
    {
    }

    Matrix<T,1>& operator=(const T& c) { this->base_apply(Assign<T>(),c); return *this; }

    Matrix<T,1>& operator=(const Matrix<T,1>& a)
    {
        return *static_cast<Matrix<T,1>*>(this)=a;
    }
};

//-----------------------------------------------------------------------------

template<class T> class Row<T,2> : public Matrix<T,2> {
public:
    Row(size_type n1, size_type n2, T* p) : Matrix<T,2>(n1,n2,p)
    {
    }
        
    Matrix<T,2>& operator=(const T& c) { this->base_apply(Assign<T>(),c); return *this; }

    Matrix<T,2>& operator=(const Matrix<T,2>& a)
    {
        return *static_cast<Matrix<T,2>*>(this)=a;
    }
};

//-----------------------------------------------------------------------------

template<class T> class Row<T,3> : public Matrix<T,3> {
public:
    Row(size_type n1, size_type n2, size_type n3, T* p) : Matrix<T,3>(n1,n2,n3,p)
    {
    }

    Matrix<T,3>& operator=(const T& c) { this->base_apply(Assign<T>(),c); return *this; }

    Matrix<T,3>& operator=(const Matrix<T,3>& a)
    {
        return *static_cast<Matrix<T,3>*>(this)=a;
    }
};

//-----------------------------------------------------------------------------
