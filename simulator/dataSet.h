#ifndef DATA_SET_H
#define DATA_SET_H

#include "range.h"
#include "stochfunction.h"
#include <cmath>


struct EuropeanOption
{
	EuropeanOption() : strike_price(0.), volatility(0.),
						interest_rate(0.), dividend(0.), force(0.),
						rebate(-1.), cap(1.e10), 
						power_symmetric(1.), power_assymmetric(1.) {}
	enum Type { Call, Put};

	double strike_price;
	double volatility;
	double interest_rate;
	double dividend;
	double force;
	//double underlying_price;
	double rebate;  // for upper barrier
	double cap;
	double power_symmetric;
	double power_assymmetric;
	EuropeanOption::Type type;

	double vanilla_value(const double& underlying_spot_price, const double& t)
	{  // dividend ?
		const double d1 = ( (log(underlying_spot_price/strike_price)) + (interest_rate + volatility * volatility / 2) * t )   / (volatility * sqrt(t));
		const double d2 = d1 - volatility * sqrt(t);
		//LOG("d1: " << d1);
		//LOG("d2: " << d2);
		const NormalDistribution n(0., 1.);
		if( type == EuropeanOption::Call)
			return n.cdf(d1) * underlying_spot_price - n.cdf(d2) * strike_price * exp(-interest_rate * t);
		else
			return n.cdf(-d2) * strike_price * exp(-interest_rate*t) - n.cdf(-d1) * strike_price;
	}
};

struct Domain
{
	Range<double> xaxis;  // space, underlying                                                                               
    Range<double> taxis;   // time
	long J, N; // x steps, t steps
};

struct DataSet
{
	EuropeanOption option;
	Domain domain;
};

#endif
