#ifndef DATA_SET_H
#define DATA_SET_H

#include "utilities.h"
#include "range.h"
#include "input_json.h"
#include <cmath>
#include <limits>



struct EuropeanOption
{
	EuropeanOption() : strike_price(0.), volatility(0.),
						interest_rate(0.), dividend(0.), force(0.),
						rebate(-1.), cap(std::numeric_limits<int>::max()),
						power_symmetric(1.), power_asymmetric(1.) {}
	enum Type { Call, Put};
	void set_strike_price(const double& value) { strike_price = value; }
	void set_volatility(const double& value)
				{ volatility = value; LOG("\tVolatility\t" << value); }
	void set_interest_rate(const double& value)
				{ interest_rate = value; LOG("\tInterest rate\t" << value); }
	void set_dividend(const double& value) { dividend = value; LOG("\tDividend\t" << value); }
	void set_force(const double& value) { force = value; LOG("\tForce\t\t" << value); }
	void set_rebate(const double& value) { rebate = value; LOG("\tRebate\t" << value); }
	void set_cap(const double& value) { cap = value; LOG("\tCap\t\t" << value); }
	void set_power_symmetric(const double& value)
				{ power_symmetric = value; LOG("\tPower symmetr.\t" << value); }
	void set_power_asymmetric(const double& value)
				{ power_asymmetric = value; LOG("\tPower asymmetr.\t" << value); }
	void set_type(const std::string& _type)
	{
			type = (boost::get<std::string>(_type) == "put") ?
					EuropeanOption::Put : EuropeanOption::Call; LOG("\tType\t\t" <<
					boost::get<std::string>(_type));
	}

	double get_strike_price() const { return strike_price; }
	double get_volatility() const { return volatility; }
	double get_interest_rate() const { return interest_rate; }
	double get_dividend() const { return dividend; }
	double get_force() const { return force; }
	double get_rebate() const { return rebate; }
	double get_cap() const { return cap; }
	double get_power_symmetric() const { return power_symmetric; }
	double get_power_asymmetric() const { return power_asymmetric; }
	Type get_type() const { return type; }
private:
	double strike_price;
	double volatility;
	double interest_rate;
	double dividend;
	double force;
	//double underlying_price;
	double rebate;  // for upper barrier
	double cap;
	double power_symmetric;
	double power_asymmetric;
	Type type;
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
