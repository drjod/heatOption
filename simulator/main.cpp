#include "stru3_matrix.h"
using namespace stru3;

#include "simulator.h"
#include "dataSet.h"
#include "input_json.h"
#include <fstream>
#include "timer.h"


int main()
{
	std::ifstream is_json("input.json");
	DataSet dataSet;
	read_data_json(is_json, dataSet);

	Timer timer;

	Simulator simulator(new TransportPDE(dataSet), dataSet.domain);
	timer.start();
	simulator.run();

	timer.stop();

	//LOG("str" << dataSet.option.strike_price);
	//std::cout << "Analyt:\n" << dataSet.domain.taxis.high() << '\n';
	/*for(int i=0; i<simulator.get_discretization().getXGrid().size();++i)
	{
		std::cout << simulator.get_discretization().getXGrid()[i] << " " 
			<< dataSet.option.vanilla_value(simulator.get_discretization().getXGrid()[i], dataSet.domain.taxis.high()) << '\n';
		std::cout << std::endl;
	}*/
	return 0;
}
