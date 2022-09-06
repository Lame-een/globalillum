#pragma once
#include <string>
#include "types.h"
#include "colors.h"

namespace Settings
{
	inline int demoIndex = -1;

	inline int samplesPerPixel = 1024;
	inline int raytracerDepth = 100;
	inline double fov = M_PI / 3;
	inline RGB bgColor = Colors::darkgray;
	inline std::string bgType = "day";
	inline bool bgIsImage = false;

	inline int imgWidth = 640;
	inline int imgHeight = 640;
	inline double gamma = 2.2;

	inline std::string imgName = "untitled";

	inline bool continuousWrite = false;

	void PrintSettings();
	void PrintHelp();
	int ArgParser(int argc, char* argv[]);
};