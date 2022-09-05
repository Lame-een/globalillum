#pragma once
#include "types.h"
#include <fstream>
#include <filesystem>

//currently write only
class Image{
public:
	Image(size_t width, size_t height);
	~Image();	

	void SetPixel(int x, int y, const RGB& color);

	void WriteFile(const std::string& path);
private:
	size_t m_Width, m_Height;
	double m_Gamma;

	char* m_Bitmap = nullptr;
};
/*
struct Image
{
	int nx, ny;
	glm::vec<3, char>* bitmap;

	Image(const int& width, const int& height) : nx(width), ny(height)
	{
		bitmap = new glm::vec<3, char>[nx * ny];
	}

	Image(const std::string& path)
	{
		std::ifstream file(path, std::ios_base::binary);

		//header
		std::string header;
		int maxval;

		file >> header;
		file >> nx;
		file >> ny;
		file >> maxval;

		bitmap = new glm::vec<3, char>[nx * ny];
		char* aux = (char*)bitmap;

		file.seekg((int)file.tellg() + 1);
		file.read(aux, nx * ny * 3);
	}

	~Image()
	{
		delete[] bitmap;
	}

	void write(const std::string& path, const std::string& name)
	{
		std::filesystem::create_directory(path);
		std::string outPath;
		outPath.reserve(path.size() + path.size() + 4);
		if((path.back() != '\\') || (path.back() != '/'))
		{
			outPath = path + '/' + name + ".ppm";
		}
		else
		{
			outPath = path + name + ".ppm";
		}

		std::ofstream file(outPath, std::ios_base::binary);
		file << "P6 " << nx << " " << ny << " 255 ";
		for(size_t i = 0; i < ny * nx; ++i)
			for(auto j = 0; j < 3; j++)
				file << bitmap[i][j];
		file.close();
	}
};
*/