#include <iostream>
#include <utility>

#include "util/image.h"
#include "objects/sphere.h"

#include "BRDF.h"
#include "camera.h"
#include "viewport.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"


int main()
{

	Camera cam({0,-2,0}, {0,1,0}, {0,0,1});
	Viewport vp(640, 640, M_PI/2);
	Image img(vp.Width(), vp.Height());
	BRDF brdf({0.5, 0.5, 0.5}, 0, 0, 1);

	Sphere sphere({0,0,0}, 1, brdf);
	for(int i = 0; i < vp.Height(); i++)
	{
		for(int j = 0; j < vp.Width(); j++)
		{
			double x = (2.0*(j+0.5) / vp.Width() - 1.0) * tan(vp.HFOV() / 2.f) * vp.AspectRatio();
			double y = (1 - 2.0*(i+0.5) / vp.Height()) * tan(vp.HFOV() / 2.f);
			Vec3 rayDir = x * cam.Right() + y * cam.Up() + cam.Dir();
			rayDir = glm::normalize(rayDir);
			RGB col = {0,0,0};
			double t = -1;
			Vec3 normal;

			if(sphere.RayIntersect(cam.Position(), rayDir, t, normal))
			{
				double scaler = glm::dot(Vec3({1,-1,1}), normal);
				col = sphere.Brdf().Diffuse() * scaler;
			}

			img.bitmap[j + i * img.nx][0] = (char)(255 * std::max(0., std::min(1., col[0])));
			img.bitmap[j + i * img.nx][1] = (char)(255 * std::max(0., std::min(1., col[1])));
			img.bitmap[j + i * img.nx][2] = (char)(255 * std::max(0., std::min(1., col[2])));
		}
	}

	img.write("./a.ppm");


	std::cout << "Light is Very Hard, yo\n";
}