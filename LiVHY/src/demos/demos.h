#pragma once
#include <unordered_map>
#include <functional>
#include "cornellBoxDiffuse.h"
#include "cornellBoxTransmissive.h"

inline std::vector<std::function<void()>> g_Demos;
inline std::vector<std::string> g_DemoNames;

inline void InitDemos()
{
	g_Demos.push_back(cornellBoxDiffuse);
	g_DemoNames.push_back("Cornell Box - diffuse");
	g_Demos.push_back(cornellBoxTransmissive);
	g_DemoNames.push_back("Cornell Box - transmissive");

	//g_Demos.push_back();
	//g_DemoNames.push_back();
}

inline void PrintDemos()
{
	std::cout << "Available demos:\n";
	for(int i = 0; i < g_DemoNames.size(); i++)
	{
		std::cout << std::setw(6) << std::setfill(' ') << i << '\t' << g_DemoNames[i] << '\n';
	}
	std::cout << std::endl;
}