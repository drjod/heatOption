#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#define LOG(x) std::cout << x << '\n'

#include "pde.h"
#include "discretization.h"
#include "double_sweep.h"
#include "assembly.h"
#include <fstream>


class Simulator
{
private:

	TransportPDE* pde;
	Discretization discretization;  // space (underlying) and time grid information

    DVec primaryVariable;  // calculated option value
	DVec delta, gamma; // secondary variables
    double time_current;
    long timeStep_current;
                                                                                                              
	TridiagonalMatrixAssembly assembly;
public:
	Simulator(TransportPDE* _pde, const Domain& _domain)
		: pde(_pde),
			discretization(_domain),
			primaryVariable(DVec(_domain.J+1)),
			gamma(DVec(_domain.J+1)), delta(DVec(_domain.J+1)),
			time_current(0.), timeStep_current(0),
		assembly(TridiagonalMatrixAssembly(pde, &discretization, .5)) // theta
		{}
	~Simulator() { delete pde; }

    void run();
    void advance();
    bool finished() const;

    DVec get_primaryVariable() const { return primaryVariable; }
    Discretization get_discretization() const { return discretization; }

	void calculate_secondaryVariables();
	void write_result(std::ostream& os);
};

void Simulator::run()
{
	// initialize
	int j = 0;
    for (auto it = std::begin(primaryVariable); it != std::end(primaryVariable); ++it, ++j )
		*it = pde->IC(discretization.getXGrid()[j]);

	LOG("IC: " << primaryVariable);
	while(time_current < discretization.getTaxis().high())
        advance();
	LOG("Result: " << primaryVariable);

	calculate_secondaryVariables();

	write_result(std::cout);
	std::ofstream os("output.dat");
	write_result(os);

}


void Simulator::advance()
{
	double t = time_current;

	// LOG("Step: " << timeStep_current << " - Time: " << t);

	assembly.configure();
	assembly.assemble_mass();
	assembly.assemble_convection(t);
	assembly.assemble_diffusion(t);
	assembly.assemble_forcing(t);
	
	//assembly.log_matrices();

	primaryVariable = double_sweep(assembly.A_implicit, assembly.B_implicit, assembly.C_implicit,
			assembly.determine_RHS(t, primaryVariable));

	//LOG(primaryVariable);

	time_current += discretization.stepSize();
	timeStep_current++;
}


void Simulator::calculate_secondaryVariables()
{
    // delta
	for(long i=1; i< discretization.numberOfNodes()-1; ++i)
        delta[i] = (primaryVariable[i+1] - primaryVariable[i-1])/(2*discretization.length());

    delta[0] = (primaryVariable[1] - primaryVariable[0])/discretization.length();                                                                       
    delta[discretization.numberOfNodes()-1] =
		(primaryVariable[discretization.numberOfNodes()-1]
				- primaryVariable[discretization.numberOfNodes()-2]) / discretization.length();                                                                       
    // gamma                                                                             
	for(long i=1; i< discretization.numberOfNodes(); ++i)
        gamma[i] = (delta[i+1] - delta[i-1])/(2*discretization.length());

    gamma[0] = (delta[1] - delta[0]) / discretization.length();
    gamma[discretization.numberOfNodes()-1] = 
		(delta[discretization.numberOfNodes()-1]
				- delta[discretization.numberOfNodes()-2]) / discretization.length();
}


void Simulator::write_result(std::ostream& os)
{
	for(long i = 0; i <discretization.getXGrid().size();++i)
		os << discretization.getXGrid()[i] << '\t' << primaryVariable[i] << '\t' 
			<< delta[i] << '\t' << gamma[i] << '\n';

}

#endif
