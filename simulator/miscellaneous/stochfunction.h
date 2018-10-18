#ifndef STOCH_FUNCTION_H
#define STOCH_FUNCTION_H

#include <cmath>


struct ProbabilityDistribution
{
	ProbabilityDistribution() = default;
	virtual ~ProbabilityDistribution() {}
};

struct ContinuousDistribution : public ProbabilityDistribution
{
	ContinuousDistribution() = default;
	ContinuousDistribution(const ContinuousDistribution&) = default;
	virtual ~ContinuousDistribution() {}

	virtual double pdf(const double& x) const = 0;
	virtual double cdf(const double& x) const = 0;

	virtual double expected() const = 0;
	virtual double variance() const = 0;
	virtual double std() const { return sqrt(variance()); }

	virtual ContinuousDistribution* clone() const = 0;
};

class NormalDistribution : public ContinuousDistribution
{
public:
	NormalDistribution() : mu(0.), sigma(1.) {}
	NormalDistribution(const double& _mu, const double& _sigma) : mu(_mu), sigma(_sigma) {}
	NormalDistribution(const NormalDistribution& n) { mu = n.mu; sigma = n.sigma; }
	~NormalDistribution() {}

	double expected(const NormalDistribution& n) const { return n.mu; }
	double variance(const NormalDistribution& n) const { return n.sigma * n.sigma; }

	double expected() const { return expected(*this); }
	double variance() const { return variance(*this); }

	double pdf(const double& x) const
	{
		const double coeff = 1./ (sqrt(2* M_PI) * sigma);
		const double fac = (x-mu) / sigma;
		return coeff * exp(-0.5 * fac * fac);
	}
	double cdf(const double& x) const
	{
		return 0.5 * (1. + std::erf( (x-mu) / (sigma * 1.4142135623731)));
	}
	ContinuousDistribution* clone() const { return new NormalDistribution(*this); }
private:
	double mu, sigma;
};


/*
double N(const double& x, F f)
{	// an abroximation
	const double a1 = 0.4361836;
	const double a2 = -0.1201676;
	const double a3 = 0.9372980;

	const double k = 1.(1. + 0.33267 * x);

	if(x>= 0.)
	{
		return 1. - f(x) * (a1 + a2*k + a3*k*k)*k;
	}
	else
	{
		return 1. -N(x);
	}
}

*/
#endif
