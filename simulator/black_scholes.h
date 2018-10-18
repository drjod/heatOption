#ifndef BLACK_SCHOLES_H
#define BLACK_SCHOLES_H

// contains characteristics

#include <iostream>
#include <algorithm>  // for min
#include <math.h>
#include "pair.h"
#include "dataSet.h"

namespace BLACK_SCHOLES
{

double diffusion_coefficient(const DataSet& dataSet, const pair<double,double>& state)
{ 
	return 0.5 * dataSet.option.volatility * dataSet.option.volatility * state.first * state.first; 
}

/*
double sigma_linear(const pair<double,double>& state)
{
	const double a=0.129;
	const double b=0.177;
	
	const double t = state.second;
	const double S = state.first;

	const double s = b+a*t;
	return 0.5*s*s*S*S;
}*/

//drift
double convection_coefficient(const DataSet& dataSet, const pair<double,double>& state)
{ 
	return (dataSet.option.interest_rate - dataSet.option.dividend) * state.first;
}

double forcing_coefficient(const DataSet& dataSet, const pair<double,double>& state)
{ 
	return dataSet.option.force; 
}

// free term
double b(const DataSet& dataSet, const pair<double,double>& state) 
{ 
	return -dataSet.option.interest_rate; 
}

// ------------------------------------------------------------------------------

// ICs - payoff functions
double IC(const DataSet& dataSet, const double& s) 
{ 
	return (s>dataSet.option.strike_price) ? 
		std::min(dataSet.option.cap, pow(s - pow(dataSet.option.strike_price, dataSet.option.power_assymmetric), 
				dataSet.option.power_symmetric)) : 0.; 
}

double IC_put(const DataSet& dataSet, const double& s) 
{
	return (s<dataSet.option.strike_price) ? 
		std::min(dataSet.option.cap, pow(pow(dataSet.option.strike_price, dataSet.option.power_assymmetric)-s, 
				dataSet.option.power_symmetric)) : 0.; 
}	

// ------------------------------------------------------------------------------

// BCs
double BC_left(const DataSet& dataSet, const double& t) 
{
	if(dataSet.option.type == EuropeanOption::Call)
		return 0.; 
	else
	{	// put
		if(dataSet.option.rebate >= 0.)
			return dataSet.option.rebate;
		else
			return IC_put(dataSet, dataSet.domain.xaxis.low()); 
	}
}

double BC_right(const DataSet& dataSet, const double& t) 
{
	if(dataSet.option.type == EuropeanOption::Call)
	{
		if(dataSet.option.rebate >= 0.)
			return dataSet.option.rebate;
		else
			return IC(dataSet, dataSet.domain.xaxis.high()); 
	}
	else  //put
		return 0.; 
}
/*
double IC_PO(const DataSet& dataSet, const double& s) 
{ 
	const EuropeanOption* const dataSet.option = dynamic_cast<const EuropeanOption* const>(instrument);
	return (pow(s,p)>dataSet.option.strike_price) ? pow(s,p)-dataSet.option.strike_price : 0.; 
}  // power dataSet.options

double IC_ASCPO(const DataSet& dataSet, const double & s)
{
	const EuropeanOption* const dataSet.option = dynamic_cast<const EuropeanOption* const>(instrument);
	const double result = (pow(s,p)>dataSet.option.strike_price) ? pow(s,p)-dataSet.option.strike_price : 0.;
	return (result<bcr) ? result : bcr;
}

double IC_SCPO(const DataSet& dataSet, const double & s) 
{
	const EuropeanOption* const dataSet.option = dynamic_cast<const EuropeanOption* const>(instrument);
	const double result = (s-dataSet.option.strike_price>0) ? pow(s-dataSet.option.strike_price,p) : 0.;
	return (result<bcr) ? result : bcr;
}
*/




/*
double BCR_PO(const DataSet& dataSet, const double& t) 
{	// Topper section 3.2.1 page 12: Power EuropeanOptions
	return pow(Xto,p)-dataSet.option.strike_price * exp(- (dataSet.option.interest_rate - dataSet.option.dividend) * (t - Yfrom)); 
}

double BCL_put(const DataSet& dataSet, const double& t)
{ 
	return dataSet.option.strike_price * exp(-(dataSet.option.interest_rate - dataSet.option.dividend) * (t - Yfrom));
} 

double BCR_Topper_p11(const DataSet& dataSet, const double & t) 
{	// Topper page 11: non-constant volatility boundary condition
	return Xto - dataSet.option.strike_price * exp(-(dataSet.option.interest_rate - dataSet.option.dividend) * (t - Yfrom)); 
}

double BCR_Topper_p10(const DataSet& dataSet, const double & t)
{	// Topper page 10: discontinuous jumps in rebate
	double result = 1;
	int i = 1;
	while( t*12 > i ){
	 result *= 2;
	 i++;
	}
	return result;
}
*/

}

#endif
