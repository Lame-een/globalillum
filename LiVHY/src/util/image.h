#pragma once
#include "types.h"
#include <fstream>
#include <filesystem>

//currently write only
class Image{
public:
	Image(size_t width, size_t height);
	Image(const std::string& path);
	~Image();	

	void SetPixel(int x, int y, const RGB& color);
	RGB GetPixel(int x, int y);
	RGB GetPixel(double u, double v);

	const Vec2i& Dimensions();
	bool IsLoaded() const;
	bool HasData() const;

	void WriteFile(const std::string& path);
private:
	Vec2i m_Dimensions;
	double m_Gamma;
	bool m_Loaded;

	unsigned char* m_Bitmap = nullptr;
};