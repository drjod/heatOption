#ifndef DISCRETIZATION_H
#define DISCRETIZATION_H

#include "range.h"
#include "dataSet.h"


class Discretization
{
	Domain domain;  // contains lower and upper boundaries
    double h, k;  // (calculated)
	DVec XARR, TARR;  // 2D-structured grid points (space and time)
public:
	//Discretization() = default;
	Discretization(const Domain& _domain) : 
				domain(_domain), 
				h(domain.xaxis.spread() / _domain.J), k(domain.taxis.spread() / _domain.N),
				XARR(DVec(_domain.J+1)),                                               
				TARR(DVec(_domain.N+1))
	 { 
		XARR[0] = domain.xaxis.low();
		TARR[0] = domain.taxis.low();

		for(auto it = std::begin(XARR)+1; it != std::end(XARR); ++it)
			*it = *(it-1) + h;
		for(auto it = std::begin(TARR)+1; it != std::end(TARR); ++it)
			*it = *(it-1) + k;

		//LOG("XGRID: " << XARR);
	}
	long numberOfNodes() const { return XARR.size(); }
	long numberOfSteps() const { return TARR.size(); }
	double length() const { return h; } 
	double stepSize() const { return k; } 
	Range<double> getXaxis() const { return domain.xaxis; }
	Range<double> getTaxis() const { return domain.taxis; }

	DVec getXGrid() const { return XARR; }
	DVec getTGrid() const { return TARR; }
};

#endif
