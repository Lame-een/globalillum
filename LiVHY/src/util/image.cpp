#include "pch.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "image.h"
#include "stbimage/stb_image_write.h"
#include "stbimage/stb_image.h"

Image::Image(size_t width, size_t height)
	: m_Dimensions(width, height), m_Gamma(1.0 / Settings::gamma), m_Loaded(false)
{
	m_Bitmap = new unsigned char[3 * width * height];
	memset(m_Bitmap, 0, 3 * width * height);
}

Image::Image(const std::string& path)
	: m_Gamma(1.0 / Settings::gamma), m_Loaded(true)
{
	int channels;
	m_Bitmap = stbi_load(path.c_str(), &m_Dimensions.x, &m_Dimensions.y, &channels, 3);

	if(m_Bitmap == NULL)
	{
		std::cout << "Unable to load image: " << path << std::endl;
	}
}

Image::~Image()
{
	if(m_Loaded)
	{
		stbi_image_free(m_Bitmap);
	}
	else
	{
		delete[] m_Bitmap;
	}
}

void Image::SetPixel(int x, int y, const RGB& color)
{
	size_t index = (y * m_Dimensions.x + x) * 3;

	m_Bitmap[index] = static_cast<unsigned char>(255 * std::clamp(std::pow(color.r, m_Gamma), 0.0, 1.0));
	m_Bitmap[index + 1] = static_cast<unsigned char>(255 * std::clamp(std::pow(color.g, m_Gamma), 0.0, 1.0));
	m_Bitmap[index + 2] = static_cast<unsigned char>(255 * std::clamp(std::pow(color.b, m_Gamma), 0.0, 1.0));
}

RGB Image::GetPixel(int x, int y)
{
	x %= m_Dimensions.x;
	y %= m_Dimensions.y;
	int index = (x + y * m_Dimensions.x)*3;
	RGB ret(m_Bitmap[index], m_Bitmap[index + 1], m_Bitmap[index + 2]);
	ret /= 255.0;
	return ret;
}

RGB Image::GetPixel(double u, double v)
{
	int x = static_cast<int>((1.0 - u) * (m_Dimensions.x - 1));
	int y = static_cast<int>((1.0 - v) * (m_Dimensions.y - 1));
	int index = (x + y * m_Dimensions.x)*3;
	RGB ret(m_Bitmap[index], m_Bitmap[index + 1], m_Bitmap[index + 2]);
	ret /= 255.0;
	return ret;
}

const Vec2i& Image::Dimensions()
{
	return m_Dimensions;
}

bool Image::IsLoaded() const
{
	return m_Loaded;
}

bool Image::HasData() const
{
	return (m_Bitmap != nullptr);
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
	stbi_write_png(outPath.c_str(), m_Dimensions.x, m_Dimensions.y, 3, m_Bitmap, 3 * sizeof(char) * m_Dimensions.x);
}
