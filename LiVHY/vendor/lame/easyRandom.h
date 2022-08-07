#pragma once
#include <random>

/*
Class which enables easy generation of random integers and doubles.
The class can be initialized and immediately used.


EasyRandom()
Default constructor. Generates a seed automatically and uses it for further generation.

EasyRandom(std::seed_seq& seed)
Constructor which takes in a custom seed for generation.

void setSeed(std::seed_seq& seed)
Set the seed of the entire class.

int getInt()
Fuction which generates and returns an integer in the range [0, 100>

int getInt(int max)
Fuction which generates and returns an integer in the range [0, max>

int getInt(int min, int max)
Fuction which generates and returns an integer in the range [min, max>

double getDouble()
Fuction which generates and returns a double in the range [0, 1>

double getDouble(double max)
Fuction which generates and returns a double in the range [0, max>

double getDouble(double min, double max)
Fuction which generates and returns a double in the range [min, max>


Example:

EasyRandom rg;
std::cout << rg.getDouble() << std::endl;
std::cout << rg.getDouble(10.0) << std::endl;
std::cout << rg.getDouble(5.0, 10.0) << std::endl;
--------------------
0.619865
9.10834
7.71358

*/

namespace lameutil
{
	class EasyRandom
	{
	private:
		std::default_random_engine generator;

	public:
		EasyRandom()
		{
			std::random_device rd;
			generator = std::default_random_engine(rd());
		}
		EasyRandom(std::seed_seq& seed)
		{
			setSeed(seed);
		}

		void setSeed(std::seed_seq& seed)
		{
			generator.seed(seed);
		}

		int getInt(int min, int max)
		{
			std::uniform_int_distribution<int> distrib;
			setDistributioni(distrib, min, max - 1);
			return distrib(generator);
		}
		int getInt(int max)
		{
			std::uniform_int_distribution<int> distrib;
			setDistributioni(distrib, 0, max - 1);
			return distrib(generator);
		}
		int getInt()
		{
			std::uniform_int_distribution<int> distrib;
			setDistributioni(distrib, 0, 100);
			return distrib(generator);
		}

		double getDouble(double min, double max)
		{
			std::uniform_real_distribution<double> distrib;
			setDistributiond(distrib, min, max);
			return distrib(generator);
		}
		double getDouble(double max)
		{
			std::uniform_real_distribution<double> distrib;
			setDistributiond(distrib, 0, max);
			return distrib(generator);
		}
		double getDouble()
		{
			std::uniform_real_distribution<double> distrib;
			setDistributiond(distrib, 0, 1);
			return distrib(generator);
		}

	private:
		void setDistributioni(std::uniform_int_distribution<int>& distrib, int min, int max)
		{
			distrib.param(std::uniform_int_distribution<int>::param_type(min, max));
		}
		void setDistributiond(std::uniform_real_distribution<double>& distrib, double min, double max)
		{
			distrib.param(std::uniform_real_distribution<double>::param_type(min, max));
		}

	};
}