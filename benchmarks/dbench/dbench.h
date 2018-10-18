#ifndef BENCHMARKING_H
#define BENCHMARKING_H


#include <vector>
#include <iostream>
#include "timer89.h"

#include <typeinfo>


namespace benchmarking
{


template<typename Func>
struct Benchmark
{
	Benchmark(Func _func, const char* _name, int _number_of_iterations) : 
		func(_func), name (_name), number_of_iterations(_number_of_iterations) {}

	double run() const
	{
		double total_time = 0.;
		std::cout << "************************************************************\n"; 
		std::cout << "************************************************************\n"; 
		for(int i=0; i<number_of_iterations; ++i)
		{	
			Timer timer;
			std::cout << "********** " << name << " " << i << '/' << number_of_iterations << '\n'; 
			// std::cout << "***** Start timer\n";
			timer.start();
			func();
			const double time_elapsed = timer.stop();
			std::cout << "***** Time elapsed (microsec): " << time_elapsed << "\n";
			std::cout << "************************************************************\n"; 
			total_time += time_elapsed;
		}
		const double average_time = total_time / number_of_iterations;
		std::cout << "***** Total time   (microsec): " << total_time << '\n';
		std::cout << "***** Average time (microsec): " << average_time << '\n';
		return average_time;
	}

	const char* get_name() const { return name; }
private:
	Func func;
	const char* name;
	int number_of_iterations;
};


template<typename Func>
struct BenchmarkCollection
{
	void add_function(Func func, const char* name="", int number_of_iterations=10)
	{
		add_benchmark(Benchmark<Func>(func, name, number_of_iterations));
	}
	void run() const
	{
		std::vector<double> time_vector;
	/*std::vector<Benchmark<Func> >::iterator it;
		for(it = benchmark_vector.begin();
				it != benchmark_vector.end(); ++it)
			it->run();*/
		for(size_t i=0; i!=benchmark_vector.size(); ++i)
			time_vector.push_back(benchmark_vector[i].run());

		std::cout << "************************************************************\n"; 
		std::cout << "************************************************************\n"; 
		std::cout << "***** SUMMARY - average times (microsec)\n"; 
		for(size_t i=0; i<benchmark_vector.size(); ++i)
			std::cout << "*****    " << time_vector[i] << '\t' << benchmark_vector[i].get_name() << '\n'; 
		std::cout << "************************************************************\n"; 

	}
private:
	void add_benchmark(Benchmark<Func> benchmark_new)
	{
		benchmark_vector.push_back(benchmark_new);
	}

	std::vector<Benchmark<Func> > benchmark_vector;	
};

BenchmarkCollection<void(*)()> collection;


} // end namespace benchmarking

#define BENCHMARK(x) namespace benchmarking { void x(); } \
void benchmarking::x()


#endif

