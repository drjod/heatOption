#ifndef GAUSS_H
#define GAUSS_H

#include <stdexcept>

// use slice function
/*template<typename T>
Row<T, 1> _slice(const DVec& v, const size_type& i, const size_type&)
{
	return v.slice(i);
}*/

/*
template<typename T>
Matrix_ref<T, 1>  __slice(Matrix_ref<T, 1> v, size_type i, size_type n)
{
	return v(slice(i, n));
}
*/

void classical_elimination(DMat& A, DVec& b)
{
	const size_type n = A.dim1();
	double pivot, mult;
	for(size_type j = 0; j != n-1; ++j)
	{
		pivot = A(j, j);		
		if(pivot == 0) throw std::runtime_error("Pivot is zero");
		for(size_type i = j+1; i != n; ++i)
		{
			mult = A(i, j) / pivot;
			//_slice<double>(A[i], j, n) =
			//	scale_and_add(_slice<double>(A[j], j, n), -mult, _slice<double>(A[i], j, n));
			A[i].slice(j) =
				scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			b(i) -= mult * b(j); 
		}
	}
}

DVec back_substitution(const DMat& A, const DVec& b)
{
	const size_type n = A.dim1();
	DVec x(n);
	double s, m;

	for(size_type i = n-1; i >= 0; --i)
	{
		//s = b(i) - dot_product(_slice<double>(A[i], i, n), _slice<double>(x, i, n));
		s = b(i) - dot_product(A[i].slice(i), x.slice(i));
		m = A(i,i);

		if(m != 0)
			x(i) = s/m;
		else
			throw std::runtime_error("Backsubstitution failure");
	}

	return x;
}


#endif
