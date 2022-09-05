#include "pch.h"
#include "settings.h"
#include "demos/demos.h"

void Settings::PrintSettings()
{
	if(demoIndex != -1)
	{
		std::cout << "Rendering demo #" << demoIndex << ": " << g_DemoNames[demoIndex] << '\n';
	}
	std::cout << "Settings: \n";
	std::cout <<
		"\tOutput name: \"" << imgName << "\"\n" <<
		"\tSamples Per Pixel: " << samplesPerPixel << '\n' <<
		"\tMaximum raytracer depth: " << raytracerDepth << '\n' <<
		"\tImage dimensions: " << imgWidth << 'x' << imgHeight << '\n' <<
		"\tCamera FOV: " << std::setprecision(3) << 180 * fov * M_1_PI << "deg\n" <<
		"\tBackground color: " << RGBtoString(bgColor) << '\n' <<
		"\tGamma: " << std::setprecision(3) << gamma << '\n' <<
		"\tContinuous file write: " << (continuousWrite ? "true\n" : "false\n") << std::endl;
}

void printOption(std::string option, std::string desc, const int& width)
{
	std::cout << std::left << std::setw(width) << std::setfill(' ') << option << desc;
}

void Settings::PrintHelp()
{
	std::cout << "Global Illumination raytracer CLI options:\n"
		<< "Usage: LiVHY.exe [OPTIONS] output_image_name\n\n"
		<< "  Raytracing options:\n";
	printOption("\t-help", "Display the help screen.\n", 20);
	printOption("\t-s, -samples ", "Set the samples per pixel. (default 2048)\n", 20);
	printOption("\t-depth ", "Set maximum recursion depth. (default 25)\n", 20);
	printOption("\t-w, -width ", "Set the viewport width. (default 640)\n", 20);
	printOption("\t-h, -height ", "Set the viewport height. (default 640)\n", 20);
	printOption("\t-fov ", "Set the camera Field Of View (in degrees). (default 60)\n", 20);
	printOption("\t-bg, -background ", "Set the scene background in hex RGB (default \"#000000\").\n", 20);
	printOption("\t-gamma ", "Set the output image gamma correction. (default 2.2)\n", 20);

	std::cout << "  Demo options:\n";
	printOption("\t-demo ", "Choose one of the raytracing demo scenes.\n", 20);
	printOption("\t-demo-list ", "List all available demos.\n", 20);
	std::cout << std::endl;
}

int Settings::ArgParser(int argc, char* argv[])
{
	for(int i = 1; i < argc; i++)
	{
		if(!strcmp(argv[i], "-help"))
		{
			PrintHelp();
			return 1;
		}
		else if(!strcmp(argv[i], "-demo-list"))
		{
			i++;
			PrintDemos();
			return 1;
		}
		else if(!strcmp(argv[i], "-demo"))
		{
			i++;
			demoIndex = std::stoi(argv[i]);
			if(demoIndex >= g_Demos.size())
			{
				demoIndex = -1;
				std::cout << "Unknown demo index " << argv[i] << "." << std::endl;
				return 1;
			}
		}
		//raytracer settings
		else if(!strcmp(argv[i], "-s") || !strcmp(argv[i], "-samples"))
		{
			i++;
			samplesPerPixel = std::max(0, std::stoi(argv[i]));
		}
		else if(!strcmp(argv[i], "-depth"))
		{
			i++;
			raytracerDepth = std::max(0, std::stoi(argv[i]));
		}
		else if(!strcmp(argv[i], "-fov"))
		{
			i++;
			fov = M_PI * std::max(0.1, std::stod(argv[i])) / 180.0;
		}
		else if(!strcmp(argv[i], "-bg") || !strcmp(argv[i], "-background"))
		{
			i++;
			bgColor = stringToRGB(argv[i]);
		}
		//image settings
		else if(!strcmp(argv[i], "-w") || !strcmp(argv[i], "-width"))
		{
			i++;
			imgWidth = std::max(1, std::stoi(argv[i]));
		}
		else if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "-height"))
		{
			i++;
			imgHeight = std::max(1, std::stoi(argv[i]));
		}
		else if(!strcmp(argv[i], "-gamma"))
		{
			i++;
			gamma = std::max(0.1, std::stod(argv[i]));
		}
		//flags
		else if(!strcmp(argv[i], "-continuous"))
		{
			continuousWrite = true;
		}
		//misc and image name
		else
		{
			if(i == argc - 1)
			{
				imgName = argv[i];
			}
			else
			{
				std::cout << "Unknown parameter " << argv[i] << std::endl;
				return 1;
			}
		}
	}

	return 0;
}