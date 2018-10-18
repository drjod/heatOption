#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include "discretization.h"
#include "myMath.h"


class TridiagonalMatrixAssembly
{
	TransportPDE* pde;
	const Discretization* const discretization;
	//Discretization* discretization;
	double factor_implicit, factor_explicit;
public:
	DVec A_explicit;
    DVec B_explicit;
    DVec C_explicit;
    DVec F_explicit;  // forcing term
    DVec G_explicit; //boundary condition

    DVec A_implicit;
    DVec B_implicit;
    DVec C_implicit;
    DVec F_implicit;   // forcing term
    DVec G_implicit;// boundary condition

public:
	TridiagonalMatrixAssembly() = default;
	TridiagonalMatrixAssembly(TransportPDE* _pde, 
				const Discretization* const _discretization, 
		const double& _theta) : 
		pde(_pde), discretization(_discretization),
				factor_implicit(_theta*discretization->stepSize()), 
				factor_explicit((1-_theta)*discretization->stepSize()) {}

	void configure()
	{
		A_explicit = DVec(discretization->numberOfNodes());
		B_explicit = DVec(discretization->numberOfNodes());
		C_explicit = DVec(discretization->numberOfNodes());
		F_explicit = DVec(discretization->numberOfNodes());
		G_explicit = DVec(discretization->numberOfNodes());
																   		  
		A_implicit = DVec(discretization->numberOfNodes());
		B_implicit = DVec(discretization->numberOfNodes());
		C_implicit = DVec(discretization->numberOfNodes());
		F_implicit = DVec(discretization->numberOfNodes());
		G_implicit = DVec(discretization->numberOfNodes());
	}

	void assemble_mass()
	{
        for (long j = 1; j < discretization->numberOfNodes()-1; j++)
		{                                             
            B_implicit[j] = B_implicit[j] - 1*discretization->length()*discretization->length();                                                                           
            B_explicit[j] = B_explicit[j] - 1*discretization->length()*discretization->length();                                                                           
		}
	}

	void assemble_convection(const double& t)
	{
        for (long j = 1; j < discretization->numberOfNodes()-1; j++)
		{
            A_implicit[j] = A_implicit[j] - 0.5 * pde->convection(discretization->getXGrid()[j], 
								t + discretization->stepSize()) * factor_implicit*discretization->length();
            A_explicit[j] = A_explicit[j] + 0.5 * pde->convection(discretization->getXGrid()[j], t)
								* factor_explicit*discretization->length();

            C_implicit[j] = C_implicit[j] + 0.5 * pde->convection(discretization->getXGrid()[j],
								t + discretization->stepSize()) * factor_implicit*discretization->length();
            C_explicit[j] = C_explicit[j] - 0.5 * pde->convection(discretization->getXGrid()[j], t)
								* factor_explicit*discretization->length();
		}
	}

	void assemble_diffusion(const double& t)
	{
        for (long j = 1; j < discretization->numberOfNodes()-1; j++)
		{
			//const double tmp_implicit = 0.5 * pde->convection(discretization->getXGrid()[j], t + discretization->stepSize()) * discretization->stepSize();
			//const double tmp_explicit = 0.5 * pde->convection(discretization->getXGrid()[j], t) * discretization->stepSize();

			//const double diffusion_implicit = tmp_implicit * coth(tmp_implicit / pde->diffusion(discretization->getXGrid()[j], t + discretization->stepSize())); 
			//const double diffusion_explicit = tmp_explicit * coth(tmp_explicit / pde->diffusion(discretization->getXGrid()[j], t)); 

            const double diffusion_implicit = pde->diffusion(discretization->getXGrid()[j], t + discretization->stepSize());
            const double diffusion_explicit = pde->diffusion(discretization->getXGrid()[j], t);

			A_implicit[j] = A_implicit[j] + diffusion_implicit * factor_implicit;
            A_explicit[j] = A_explicit[j] - diffusion_explicit * factor_explicit;

            B_implicit[j] = B_implicit[j] - 2 * diffusion_implicit * factor_implicit;
            B_explicit[j] = B_explicit[j] + 2 * diffusion_explicit * factor_explicit;

            C_implicit[j] = C_implicit[j] + diffusion_implicit * factor_implicit;
            C_explicit[j] = C_explicit[j] - diffusion_explicit * factor_explicit;
		}
	}

	void assemble_forcing(const double& t)
	{
        for (long j = 1; j < discretization->numberOfNodes()-1; j++)
		{
            F_implicit[j] = F_implicit[j] - pde->forcing(discretization->getXGrid()[j],
							t + discretization->stepSize()) * factor_implicit;  // RHS->forcing
            F_explicit[j] = F_explicit[j] + pde->forcing(discretization->getXGrid()[j], t) * factor_explicit;
		}
	}

	DVec determine_RHS(const double& t, const DVec& primaryVariable)
	{
		DVec RHS(discretization->numberOfNodes());
        for (long j = 1; j < discretization->numberOfNodes()-1; j++)
		{
            RHS[j] = A_explicit[j] * primaryVariable[j-1] 
						+ B_explicit[j] * primaryVariable[j] 
						+ C_explicit[j] * primaryVariable[j+1];
		}

		//BCs
		RHS[0] = pde->BCL(t);
		RHS[discretization->numberOfNodes()-1] = pde->BCR(t);
		
		return RHS;
	}

	void log_matrices()
	{
		LOG("A_explicit:" << A_implicit);
		LOG("B_explicit:" << B_implicit);
		LOG("C_explicit:" << C_implicit);

		//LOG("A_implicit:" << A_implicit);
		//LOG("B_implicit:" << B_implicit);
		//LOG("C_implicit:" << C_implicit);
	}
};


#endif
