#pragma once
#include <iostream>
#include <iomanip>

/*
The class must be initialized before the for loop with the loop iterator and the limiting variable of the loop.
The bar() function must be appended to the end of the for loop in order for it to print out the loading bar to the standard output.


LoadingBar(int& iter, int& limit, const char* sign = "<")
	iter - the iterator of the for loop
	limit - the limit variable in the loop
	sign - (optional) it's used to check which kind of for loop it is: valid inputs are "<", ">", "<=", ">="

void setBarSize(const int size) 
Resizes the loading bar

void bar()
Must be appended to the end of the for loop


Example:

int i = 1;
int lim = 100;
LoadingBar bar(i, lim, "<=");
bar.setBarSize(20);
for(;i <= lim; i++){
	...
	bar.bar();
}

*/

namespace lameutil
{

	class LoadingBar
	{
	public:
		LoadingBar() = delete;
		LoadingBar(const LoadingBar& oth) = delete;

		LoadingBar(int& iter, int& limit, const char* sign = "<") : pIter(&iter), limit(limit)
		{
			parse(sign);
			init();
		}
		~LoadingBar()
		{
			std::cout << std::endl;
		}

		void setBarSize(const int size)
		{
			barSize = size;
		}

		void bar()
		{
			if(sign < 2)
			{
				iter = (float)*pIter;
			}
			else
			{
				iter = (float)(limit - *pIter);
			}

			print();
		}
	private:
		enum Sign : int
		{
			LESS = 0, LESSEQ = 1, MORE = 2, MOREEQ = 3
		};

		int* pIter;
		float iter;
		int limit;

		int barSize = 20;

		Sign sign = Sign::LESS;


		void parse(const char* str)
		{
			if(str[0] == '<')
			{
				if(str[1] != '\0')
					sign = Sign::LESSEQ;
				else
					sign = Sign::LESS;
			}
			else
			{
				if(str[1] != '\0')
					sign = Sign::MOREEQ;
				else
					sign = Sign::MORE;
			}
		}

		void init()
		{
			if(sign > 1)
			{
				limit = *pIter - limit;
				limit++;
			}

			if(sign == Sign::LESS || sign == Sign::MORE)
			{
				limit--;
			}

		}

		void print()
		{
			float percentage = iter / limit;
			int completed = (int)(barSize * percentage);
			
			std::cout << "\r";
			std::cout << '|';
			for(int i = 0; i < completed; i++)
			{
				std::cout << '#';
			}
			for(int i = 0; i < barSize - completed; i++)
			{
				std::cout << '-';
			}
			std::cout << "| " << iter << "/" << limit << " " << std::setprecision(3) << (percentage * 100) << "%    " << std::flush;
		}

	};
}