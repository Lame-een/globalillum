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
		"\tGamma: " << std::setprecision(3) << gamma << '\n' <<
		"\tContinuous file write: " << (continuousWrite ? "true\n" : "false\n");
	if(bgIsImage)
	{
		std::cout <<
			"\tBackground image: " << bgType << std::endl;
	}
	else
	{
		std::cout <<
			"\tBackground color: " << RGBtoString(bgColor) << '\n' << std::endl;
	}
}

void printOption(std::string option, std::string desc, const int& width)
{
	std::cout << std::left << std::setw(width) << std::setfill(' ') << option << desc;
}

void Settings::PrintHelp()
{
	const int columnSpace = 30;

	std::cout << "Global Illumination raytracer CLI options:\n"
		<< "Usage: LiVHY.exe [OPTIONS] output_image_name\n\n"
		<< "  Raytracing options:\n";
	printOption("\t-help", "Display the help screen.\n", columnSpace);
	printOption("\t-s, -samples ", "Set the samples per pixel. (default 1024)\n", columnSpace);
	printOption("\t-depth ", "Set maximum recursion depth. (default 25)\n", columnSpace);
	printOption("\t-w, -width ", "Set the viewport width. (default 640)\n", columnSpace);
	printOption("\t-h, -height ", "Set the viewport height. (default 640)\n", columnSpace);
	printOption("\t-fov ", "Set the camera Field Of View (in degrees). (default 60)\n", columnSpace);
	printOption("\t-bg, -background ", "Set the scene background in hex RGB (default \"#3a3a3a\").\n", columnSpace);
	printOption("\t-bgimg, -background-image ", "Set the scene background to \"day\" or \"night\" (default \"none\").\n", columnSpace);
	printOption("\t-gamma ", "Set the output image gamma correction. (default 2.2)\n", columnSpace);

	std::cout << "  Demo options:\n";
	printOption("\t-demo ", "Choose one of the raytracing demo scenes.\n", columnSpace);
	printOption("\t-demo-list ", "List all available demos.\n", columnSpace);
	std::cout << "(Note: All options are case sensitive.)\n";
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
			fov = c_Pi * std::max(0.1f, std::stof(argv[i])) / 180.0f;
		}
		else if(!strcmp(argv[i], "-bg") || !strcmp(argv[i], "-background"))
		{
			i++;
			bgColor = stringToRGB(argv[i]);
		}
		else if(!strcmp(argv[i], "-bgimg") || !strcmp(argv[i], "-background-image"))
		{
			i++;
			if(!strcmp(argv[i], "day") || !strcmp(argv[i], "night") || !strcmp(argv[i], "debug"))
			{
				bgIsImage = true;
				bgType = argv[i];
			}
			else
			{
				std::cout << "Unknown parameter " << argv[i] << " for background image." << std::endl;
				return 1;
			}
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
			gamma = std::max(0.1f, std::stof(argv[i]));
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