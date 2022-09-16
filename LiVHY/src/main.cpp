#include "pch.h"

#include "demos/demos.h"
#include "demos/sandbox.h"

#include "raytracer.h"

int main(int argc, char* argv[])
{
	InitDemos();

	if(Settings::ArgParser(argc, argv))
	{
		return 1;
	}
	else
	{
		Settings::PrintSettings();
	}

	lameutil::g_TimerPrecision = lameutil::TimerType::SEC;
	{
		lameutil::BenchTimer timer;
		if(Settings::demoIndex != -1)
		{
			g_Demos[Settings::demoIndex]();
		}
		else
		{
			sandbox();
		}
	}
	return 0;
}