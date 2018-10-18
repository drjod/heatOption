#ifndef MATRIX_ET_H
#define MATIRX_ET_H

// expression templates
//-------------------------------------------------------------------
// addition
template<typename Op1, typename Op2>
struct MatrixAdd
{
	typedef typename Op1::value_type value_type;

	const Op1& op1;
	const Op2& op2;

	MatrixAdd(const Op1& _op1, const Op2& op2) : op1(_op1), op2(op2) {}

	value_type element(size_type i) const { return op1.element(i) + op2.element(i); }
};


template<typename Op1, typename Op2>
MatrixAdd<Op1 , Op2> 
operator+(const Op1& m1, const Op2& m2)
{
	return MatrixAdd<Op1, Op2>(m1, m2);
}

//-------------------------------------------------------------------
// subtraction

template<typename Op1, typename Op2>
struct MatrixSub
{
	typedef typename Op1::value_type value_type;

	const Op1& op1;
	const Op2& op2;

	MatrixSub(const Op1& _op1, const Op2& op2) : op1(_op1), op2(op2) {}

	value_type element(size_type i) const { return op1.element(i) - op2.element(i); }
};


template<typename Op1, typename Op2>
MatrixSub<Op1 , Op2> 
operator-(const Op1& m1, const Op2& m2)
{
	return MatrixSub<Op1, Op2>(m1, m2);
}

#endif
