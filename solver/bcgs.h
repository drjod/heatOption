#ifndef BCGS_H
#define BCGS_H

#include <cmath>


double max(const DVec& v, const double& c)
{
	double result = 0.;
	for(size_type i=0; i!=v.size(); ++i)
		if(fabs(v(i)*c) > result)
			result = fabs(v(i)*c);

	return result;
}

double bcgs(const DMat& A, const DVec& b, DVec& x,
	const double accuracy=1.e-10, long max_iterations=10000)
{
	double rho = 1., alpha = 1., omega = 1.;
	double accuracy_reached = -1.;
	DVec r_0(b.dim1());
	r_0 = b - A*x;
	DVec r = r_0;
	DVec v(r.dim1());
	DVec p(r.dim1());
	DVec h(r.dim1()), s(r.dim1()), t(r.dim1());

	int i;
	for(i=0; i<max_iterations; ++i)
	{
		double beta = 1. / rho;
		rho = dot_product(r_0, r);

		beta *= rho * alpha / omega;
		p = scale_and_add(scale_and_add(v, -omega, p), beta, r);
		v = A * p;
		alpha = rho / dot_product(r_0, v);
		h = scale_and_add(p, alpha, x);
		double accuracy_reached = max(p, alpha);
		if(accuracy_reached < accuracy)
			break;
		s = scale_and_add(v, -alpha, r);
		t = A * s;
		omega = dot_product(t, s) / dot_product(t, t);
		x = scale_and_add(s, omega, h);
		r = scale_and_add(t, -omega, s);

	}
	std::cout << "Iterations: " << i << '\n';
	
	return accuracy_reached;
}

#endif
