/// @file objects/areaLight.h
#pragma once
#include "light.h"
#include "scene.h"

/// @class AreaLight 
/// @brief A simple area light
//TODO: implement fully
class AreaLight : public Light
{
public:
	AreaLight();
	AreaLight(const Vec3& pos, const Vec3& edge1, const Vec3& edge2, 
			  const Vec2& dimensions, const RGB& color, double intensity);

	void SetEdge(int index, const Vec3& vec);
	void SetDimension(const Vec2& dim);

	const Vec3& Edge(int index) const;
	const Vec2& Dimensions() const;
	const Vec3& Normal() const;
	const double Area() const;

	RGB DiffuseReflection(const HitInfo& hitInfo) const override;
	RGB SpecularReflection(const HitInfo& hitInfo) const override;
	RGB Reflection(const HitInfo& hitInfo) const override;

	void LightReflection(const Scene& scene, const HitInfo& hitInfo, RGB& color) const override;

private:
	Vec2 m_Dim = Vec2(1.0, 1.0);
	Vec3 m_Edges[2] = {Vec3(1.0,0.0,0.0), Vec3(0.0,1.0,0.0)};
	Vec3 m_Normal;
	double m_Area;
};