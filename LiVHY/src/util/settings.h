#pragma once
#include <string>
#include "types.h"
#include "colors.h"
#include "math.h"

namespace Settings
{
	inline int demoIndex = -1;

	inline int samplesPerPixel = 1024;
	inline int raytracerDepth = 100;
	inline float fov = c_Pi / 3.0f;
	inline RGB bgColor = Colors::darkgray;
	inline std::string bgType = "day";
	inline bool bgIsImage = false;

	inline int imgWidth = 640;
	inline int imgHeight = 640;
	inline float gamma = 2.2f;

	inline std::string imgName = "untitled";

	inline bool continuousWrite = false;

	void PrintSettings();
	void PrintHelp();
	int ArgParser(int argc, char* argv[]);
};