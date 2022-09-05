#include "pch.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "image.h"
#include "stbimage/stb_image_write.h"

Image::Image(size_t width, size_t height)
	: m_Width(width), m_Height(height), m_Gamma(1.0 / Settings::gamma)
{
	m_Bitmap = new char[3 * width * height];
	memset(m_Bitmap, 0, 3 * width * height);
}

Image::~Image()
{
	delete[] m_Bitmap;
}

void Image::SetPixel(int x, int y, const RGB& color)
{
	size_t index = (y * m_Width + x) * 3;

	m_Bitmap[index] = static_cast<char>(255 * std::clamp(pow(color.r, m_Gamma), 0.0, 1.0));
	m_Bitmap[index + 1] = static_cast<char>(255 * std::clamp(pow(color.g, m_Gamma), 0.0, 1.0));
	m_Bitmap[index + 2] = static_cast<char>(255 * std::clamp(pow(color.b, m_Gamma), 0.0, 1.0));
}

void Image::WriteFile(const std::string& path)
{
	std::filesystem::create_directory(path);
	std::string outPath;
	outPath.reserve(path.size() + path.size() + 4);
	if((path.back() != '\\') || (path.back() != '/'))
	{
		outPath = path + '/' + Settings::imgName + ".png";
	}
	else
	{
		outPath = path + Settings::imgName + ".png";
	}
	stbi_write_png(outPath.c_str(), (int)m_Width, (int)m_Height, 3, m_Bitmap, (int)(3 * sizeof(char) * m_Width));
}
