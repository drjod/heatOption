#ifndef PDE_H
#define PDE_H


#include "detfunction.h"
//#include "range.h"
//#include "pair.h"
#include <functional>
#include "dataSet.h"
#include "black_scholes.h"


// Advective-diffusive
class TransportPDE
{
public:
	TransportPDE() = default;
	TransportPDE(const DataSet& dataSet)
	{
		std::cout << "construct transport pde\n";
		_diffusion = TwoVarDFunction<double, double, double>(
			std::bind(BLACK_SCHOLES::diffusion_coefficient, std::ref(dataSet), std::placeholders::_1));
		_convection = TwoVarDFunction<double, double, double>(
			std::bind(BLACK_SCHOLES::convection_coefficient, std::ref(dataSet), std::placeholders::_1));
		b = TwoVarDFunction<double, double, double>(
			std::bind(BLACK_SCHOLES::b, std::ref(dataSet), std::placeholders::_1));
		_forcing = TwoVarDFunction<double, double, double>(
			std::bind(BLACK_SCHOLES::forcing_coefficient, std::ref(dataSet), std::placeholders::_1));

		ic = (dataSet.option.get_type() == EuropeanOption::Call)?
				AtomicDFunction<double, double>(std::bind(BLACK_SCHOLES::IC_call, std::ref(dataSet), std::placeholders::_1)) :
				AtomicDFunction<double, double>(std::bind(BLACK_SCHOLES::IC_put, std::ref(dataSet), std::placeholders::_1));
		bcl = AtomicDFunction<double, double>(
			std::bind(BLACK_SCHOLES::BC_left, std::ref(dataSet), std::placeholders::_1));
		bcr = AtomicDFunction<double, double>(
			std::bind(BLACK_SCHOLES::BC_right, std::ref(dataSet), std::placeholders::_1));	
	}

	TwoVarDFunction<double, double, double> _diffusion, _convection, b, _forcing;
	AtomicDFunction<double, double> ic;
	AtomicDFunction<double, double> bcl, bcr;
                                                                                                              
	// selector functions
	TwoVarDFunction<double, double, double> diffusion() const { return _diffusion; }
	TwoVarDFunction<double, double, double> convection() const { return _convection; }
	TwoVarDFunction<double, double, double> zeroterm() const { return b; }
	TwoVarDFunction<double, double, double> RHS() const { return _forcing; }

	AtomicDFunction<double, double> BCL() const { return bcl; }
	AtomicDFunction<double, double> BCR() const { return bcr; }
	AtomicDFunction<double, double> IC() const { return ic; }
	// modifier functions
	void diffusion(TwoVarDFunction<double, double, double>& new_function) {  _diffusion = new_function; }
	void convection(TwoVarDFunction<double, double, double>& new_function) {  _convection = new_function; }
	void zeroterm(const TwoVarDFunction<double, double, double>& new_function) { b = new_function; }
	void RHS(const TwoVarDFunction<double, double, double>& new_function) { _forcing = new_function; }
                                                                                                              
	void BCL(const AtomicDFunction<double, double>& new_function) { bcl = new_function; }
	void BCR(const AtomicDFunction<double, double>& new_function) { bcr = new_function; }
	void IC(const AtomicDFunction<double, double>& new_function) { ic = new_function; }
	
	// characteristics - call functions
	double diffusion(const double& xvalue, const double& tvalue) const
			{ return _diffusion.calculate(pair<double, double>(xvalue, tvalue)); }
	double convection(const double& xvalue, const double& tvalue) const
			{ return _convection.calculate(pair<double, double>(xvalue, tvalue)); }
	double zeroterm(const double& xvalue, const double& tvalue) const
			{ return b.calculate(pair<double, double>(xvalue, tvalue)); }
	double forcing(const double& xvalue, const double& tvalue) const
			{ return _forcing.calculate(pair<double, double>(xvalue, tvalue)); }
	// Boundary and initial conditions - call functions
	double BCL(const double& tvalue) const { return bcl.calculate(tvalue); }
	double BCR(const double& tvalue) const { return bcr.calculate(tvalue); }
	double IC(const double& xvalue) const { return ic.calculate(xvalue); }
};

#endif
