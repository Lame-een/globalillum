#pragma once
#include <iostream>
#include <chrono>

/*
RAII based timer class.

Usage:
    Wrap the piece of code you want to measure into a scope.
    Construct the class at the beginning of the scope
    At the end of the scope the class gets destroyed and prints out the time elapse since construction to the standard output.

    OR

    Use the:
        BENCHMARK_SCOPE(scopeName) - for benchmarking a scope
        BENCHMARK_FUNCTION() - for benchmarking a function
    macros while defining
        #define BENCHMARKING 1
    before the header


To change the precision of the timer, redefine the global variable g_TimerPrecision
*/

#if BENCHMARKING 1
#define BENCHMARK_SCOPE(scopeName) lameutil::BenchTimer timer##__LINE__(scopeName)
#define BENCHMARK_FUNCTION() BENCHMARK_SCOPE(__FUNCSIG__)
#else 
#define BENCHMARK_SCOPE(scopeName)
#define BENCHMARK_FUNCTION()
#endif

namespace lameutil
{
    enum class TimerType
    {
        MICRO, MILLI, SEC
    };

    static TimerType g_TimerPrecision = TimerType::MILLI;
    
    class BenchTimer
    {
    public:

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> startTime;

        std::string name;
    public:

        BenchTimer() : name{}
        {
            startTime = std::chrono::high_resolution_clock::now();
        }

        BenchTimer(std::string name) : name{name}
        {
            startTime = std::chrono::high_resolution_clock::now();
        }

        ~BenchTimer()
        {
            std::chrono::time_point<std::chrono::high_resolution_clock> endTime = std::chrono::high_resolution_clock::now();

            std::cout << "Timer " << name << ": ";

            if(g_TimerPrecision == TimerType::MICRO)
            {
                std::cout << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << " us";
            }
            else if(g_TimerPrecision == TimerType::MILLI)
            {
                std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms";
            }
            else
            {
                std::cout << std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count() << " s";
            }
            std::cout << std::endl;
        }
    };
}