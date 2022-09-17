#include "pch.h"
#include "cubemap.h"

CubeMap::CubeMap(const std::string& folderPath)
{
	std::cout << "Loading cubemap images..." << std::endl;
	for(int i = 0; i < 6; i++)
	{
		m_Images[i] = new Image(folderPath + c_ImgNames[i]);
		m_Loaded &= m_Images[i]->HasData();
	}

	if(m_Loaded)
	{
		std::cout << "Cubemap loaded." << std::endl;
	}
	else
	{
		std::cout << "Unable to load cubemap." << std::endl;
	}
}
CubeMap::~CubeMap()
{
	for(int i = 0; i < 6; i++)
	{
		delete m_Images[i];
	}
}

RGB CubeMap::Sample(const Vec3& dir) const
{
	int index = -1;
	Vec2 uv = VecToUV(dir, index);
	return m_Images[index]->GetPixel(uv.x, uv.y);
}

bool CubeMap::Loaded() const
{
	return m_Loaded;
}

Vec2 CubeMap::VecToUV(const Vec3& dir, int& imgIndex) const
{
	double absX = std::abs(dir.x);
	double absY = std::abs(dir.y);
	double absZ = std::abs(dir.z);

	double maxAxis, uc, vc;

	if(dir.x > 0)
	{
		if(absX >= absY && absX >= absZ)
		{
			// u (0 to 1) goes from -y to +y
			// v (0 to 1) goes from -z to +z
			maxAxis = absX;
			uc = dir.y;
			vc = dir.z;
			imgIndex = 0;
		}
	}
	else
	{
		if(absX >= absY && absX >= absZ)
		{
			// u (0 to 1) goes from +y to -y
			// v (0 to 1) goes from -z to +z
			maxAxis = absX;
			uc = -dir.y;
			vc = dir.z;
			imgIndex = 1;
		}
	}

	if(dir.y > 0)
	{
		if(absY >= absX && absY >= absZ)
		{
			// u (0 to 1) goes from +x to -x
			// v (0 to 1) goes from -z to +z
			maxAxis = absY;
			uc = -dir.x;
			vc = dir.z;
			imgIndex = 2;
		}
	}
	else
	{
		if(absY >= absX && absY >= absZ)
		{
			// u (0 to 1) goes from -x to +x
			// v (0 to 1) goes from -z to +z
			maxAxis = absY;
			uc = dir.x;
			vc = dir.z;
			imgIndex = 3;
		}
	}

	if(dir.z > 0)
	{
		if(absZ >= absX && absZ >= absY)
		{
			// u (0 to 1) goes from +x to -x
			// v (0 to 1) goes from +y to -y
			maxAxis = absZ;
			uc = -dir.x;
			vc = -dir.y;
			imgIndex = 4;
		}
	}
	else
	{
		if(absZ >= absX && absZ >= absY)
		{
			// u (0 to 1) goes from -x to +x
			// v (0 to 1) goes from +y to -y
			maxAxis = absZ;
			uc = dir.x;
			vc = -dir.y;
			imgIndex = 5;
		}
	}

	// Convert range from -1 to 1 to 0 to 1
	return Vec2(0.5 * (uc / maxAxis + 1.0), 0.5 * (vc / maxAxis + 1.0));
}