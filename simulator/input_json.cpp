#ifndef INPUT_JSON_H
#define INPUT_JSON_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "json_grammar.cpp"

#include "dataSet.h"
#include "range.h"
#include "input_json.h"


EuropeanOption set_europeanOption(parser::Object object);
Domain set_domain(parser::Object object);
void set_range(parser::Object object, Range<double>& range, long& numberOfSteps);
//void set_boundary_conditions(parser::Object object, DataSet& dataSet);
//BoundaryCondition set_BC(parser::Object object);


void read_data_json(std::istream& is, DataSet& dataSet)
{
	// parse file	
	std::string json_text(std::istreambuf_iterator<char>(is), {});

	auto it = json_text.begin();

	parser::JSON_grammar<std::string::iterator, qi::space_type> grammar;
                                                                                                              
    parser::Value result;                                                                                                  
    if(qi::phrase_parse(it, json_text.end(), grammar, qi::space, result) &&                                          
        it == json_text.end())
	{
		// boost::apply_visitor(parser::JSONPrinter(), result);
		// std::cout << "\n"; 
	}
	else
		std::cout << "Not JSON\n";

	// set objects
	parser::Object root = boost::get<parser::Object>(result);

	//DataSet dataSet;
	for(auto it = root.begin(); it != root.end(); ++it)
	{
		if(it->first == "european option")
		{
			std::cout << "Set european option\n";
			dataSet.option = set_europeanOption(
					boost::get<parser::Object>(it->second));
		}
		else if(it->first == "domain")
		{
			std::cout << "Set computational domain\n";
			dataSet.domain = set_domain(boost::get<parser::Object>(it->second));
		}
		/*else if(it->first == "boundary conditions")
		{
			std::cout << "Set boundary conditions\n";
			set_boundary_conditions(boost::get<parser::Object>(it->second), dataSet);
		}*/
		else
			std::cout << "Error in model specification: Object unknown\n";
	}

	std::cout << "Finished initializing options and domain\n";
	//return dataSet;
}


EuropeanOption set_europeanOption(parser::Object object)
{
	EuropeanOption option;
	for(auto it = object.begin(); it != object.end(); ++it)
	{
		if(it->first == "type")
		{
			option.set_type(boost::get<std::string>(it->second));
		}
		else if(it->first == "strike price")
		{
			option.set_strike_price(boost::get<double>(it->second));
		}
		else if(it->first == "volatility")
		{
			option.set_volatility(boost::get<double>(it->second));
		}
		else if(it->first == "interest rate")
		{
			option.set_interest_rate(boost::get<double>(it->second));
		}
		else if(it->first == "dividend")
		{
			option.set_dividend(boost::get<double>(it->second));
		}
		else if(it->first == "forcing term")
		{
			option.set_force(boost::get<double>(it->second));
		}
		else if(it->first == "rebate")
		{
			option.set_rebate(boost::get<double>(it->second));
		}
		else if(it->first == "cap")
		{
			option.set_cap(boost::get<double>(it->second));
		}
		else if(it->first == "symmetric power")
		{
			option.set_power_symmetric(boost::get<double>(it->second));
		}
		else if(it->first == "asymmetric power")
		{
			option.set_power_asymmetric(boost::get<double>(it->second));
		}
		else
		{
			std::cout << it->first << '\n';
			std::cout << "Error in model specification: European option\n";
		}
	}
	return option;
}


Domain set_domain(parser::Object object)
{
	Domain domain;
	for(auto it = object.begin(); it != object.end(); ++it)
	{
		if(it->first == "underlying")
		{
			set_range(boost::get<parser::Object>(it->second), domain.xaxis, domain.J);
		}
		else if(it->first == "time")
		{
			set_range(boost::get<parser::Object>(it->second), domain.taxis, domain.N);
		}
		else
			std::cout << "Error in model specification: Domain\n";
	}
	return domain;

}

void set_range(parser::Object object, Range<double>& range, long& numberOfSteps)
{
	for(auto it = object.begin(); it != object.end(); ++it)
	{
		if(it->first == "minimum")
		{
			range.low(boost::get<double>(it->second));
		}
		else if(it->first == "maximum")
		{
			range.high(boost::get<double>(it->second));
		}
		else if(it->first == "steps")
		{
			numberOfSteps = (long)boost::get<double>(it->second);  // autsch
		}
		else
			std::cout << "Error in model specification: Range\n";
	}
}


/*
void set_boundary_conditions(parser::Object object, DataSet& dataSet)
{
	for(auto it = object.begin(); it != object.end(); ++it)
	{
		if(it->first == "left")
		{
			dataSet.BC_left = set_BC(boost::get<parser::Object>(it->second));
		}
		else if(it->first == "right")
		{
			dataSet.BC_right = set_BC(boost::get<parser::Object>(it->second));
		}
		else
			std::cout << "Error in model specification: Domain\n";
	}
}

BoundaryCondition set_BC(parser::Object object)
{
	BoundaryCondition bc;
	for(auto it = object.begin(); it != object.end(); ++it)
	{
		if(it->first == "type")
		{
			std::string tmp = boost::get<std::string>(it->second);
			if(tmp == "constant") bc.type == BoundaryCondition::constant;
			else if(tmp == "power") bc.type == BoundaryCondition::power;
			else if(tmp == "topper 1") bc.type == BoundaryCondition::topper_1;
			else if(tmp == "topper 2") bc.type == BoundaryCondition::topper_2;
		}
		else if(it->first == "value")
		{
			bc.value = boost::get<double>(it->second);
		}
		else
			std::cout << "Error in model specification: Range\n";
	}

	return bc;
}
*/
#endif
