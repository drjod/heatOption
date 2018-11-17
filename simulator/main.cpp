#include "stru3_matrix.h"
using namespace stru3;

#include "simulator.h"
#include "dataSet.h"
#include "input_json.h"
#include <fstream>
#include "timer.h"


int main(int argc, char *argv[])
{
	std::ifstream is_json(argv[1]);
	DataSet dataSet;
	read_data_json(is_json, dataSet);

	Timer timer;

	Simulator simulator(new TransportPDE(dataSet), dataSet.domain);
	timer.start();
	simulator.run();

	timer.stop();

	return 0;
}
