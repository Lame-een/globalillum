#pragma once
#include "util/image.h"
#include <string>
#include <array>

class CubeMap
{
public:
	CubeMap(const std::string& folderPath);
	~CubeMap();

	RGB Sample(const Vec3& dir) const;
	bool Loaded() const;

private:
	Vec2 VecToUV(const Vec3& dir, int& imgIndex) const;

	Image* m_Images[6];

	bool m_Loaded = true;

	const std::array<std::string, 6> c_ImgNames = {"posx.png", "negx.png", "posy.png", "negy.png", "posz.png", "negz.png"};
};

