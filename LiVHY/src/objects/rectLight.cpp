#include "pch.h"
#include "RectLight.h"
#include "util/tracerConsts.h"

RectLight::RectLight() : Light(LightType::Rect)
{
	m_Normal = glm::normalize(glm::cross(m_Edges[0], m_Edges[1]));
}

RectLight::RectLight(const Vec3& pos, const Vec3& edge1, const Vec3& edge2, const Vec2& dimensions, const RGB& color, double intensity)
	: Light(pos, color, intensity, LightType::Rect), m_Dim(dimensions),
	m_Edges{glm::normalize(edge1) * dimensions[0], glm::normalize(edge2) * dimensions[1]},
	m_Area(glm::length(glm::cross(m_Edges[0], m_Edges[1])))
{
	m_Normal = glm::normalize(glm::cross(m_Edges[0], m_Edges[1]));
}

void RectLight::SetEdge(int index, const Vec3& vec)
{
	m_Edges[index] = vec;
	m_Normal = glm::normalize(glm::cross(m_Edges[0], m_Edges[1]));
}

void RectLight::SetDimension(const Vec2& dim)
{
	m_Dim = dim;
}

const Vec3& RectLight::Edge(int index) const
{
	return m_Edges[index];
}

const Vec2& RectLight::Dimensions() const
{
	return m_Dim;
}

const Vec3& RectLight::Normal() const
{
	return m_Normal;
}

const double RectLight::Area() const
{
	return m_Area;
}

RGB RectLight::DiffuseReflection(const HitInfo& hitInfo) const
{
	return RGB();
}

RGB RectLight::SpecularReflection(const HitInfo& hitInfo) const
{
	return RGB();
}

RGB RectLight::Reflection(const HitInfo& hitInfo) const
{
	return RGB();
}

void RectLight::LightReflection(const Scene& scene, const HitInfo& hitInfo, RGB& color) const
{
	const BRDF& brdf = *hitInfo.object->Brdf();

	//check if in front of light
	if(glm::dot(m_Normal, hitInfo.point - m_Pos) < 0)
	{
		return;
	}

	int totalHits = 0;
	int totalSamples = 0;

	if(brdf.IsDiffuse())
	{
		int sampleNum = static_cast<int>(m_Area * c_LightSampleNum + 1);
		totalSamples += sampleNum;
		int hits = 0;
		double weight = 0;
		for(int i = 0; i < sampleNum; i++)
		{
			double r0 = lameutil::g_RandGen.getDouble() - 0.5;
			double r1 = lameutil::g_RandGen.getDouble() - 0.5;

			//computing random sample point on the light
			Vec3 samplePoint = r0 * m_Edges[0] + r1 * m_Edges[1] + m_Pos;
			if(!scene.OcclusionTest(GetDisplacedPoint(hitInfo), samplePoint))
			{
				hits++;

				double intensity = m_Intensity / glm::distance2(hitInfo.point, samplePoint);

				Vec3 l = glm::normalize(samplePoint - hitInfo.point); //vector towards the light

				//reducing intensity by cosine between normal and ray (the probability of emission)
				intensity *= glm::dot(m_Normal, -l) * 2.0;

				//diffuse reflection
				weight += intensity * glm::abs(glm::dot(m_Normal, l));
			}
		}
		if(hits > 0)
		{
			totalHits += hits;
			color += weight * m_Color * brdf.Color() * (m_Area / hits);
		}
	}

	if(brdf.IsSpecular())
	{
		double weight = 0;
		int hits = 0;
		int sampleNum = static_cast<int>(m_Area * c_LightSampleNum + 1) * 2;
		totalSamples += sampleNum;

		Vec3 v = -hitInfo.ray.Dir();    //vector towards eye

		for(int i = 0; i < sampleNum; i++)
		{
			//computing random sample point on the light
			double r0 = lameutil::g_RandGen.getDouble() - 0.5;
			double r1 = lameutil::g_RandGen.getDouble() - 0.5;
			Vec3 samplePoint = r0 * m_Edges[0] + r1 * m_Edges[1] + m_Pos;

			if(!scene.OcclusionTest(GetDisplacedPoint(hitInfo), samplePoint))
			{
				hits++;

				double intensity = m_Intensity / glm::distance2(hitInfo.point, samplePoint);

				Vec3 l = glm::normalize(samplePoint - hitInfo.point); //vector towards the light
				double nl = glm::dot(hitInfo.normal, l);
				Vec3 r = (2.0 * nl) * hitInfo.normal - l; //reflected light ray
				double vr = glm::dot(v, r);

				if(vr < c_Epsilon) continue;

				//reducing intensity by cosine between normal and ray (the probability of emission)
				intensity *= glm::dot(m_Normal, -l) * 2.0;

				//diffuse reflection
				weight += intensity * glm::pow(vr, brdf.Shininess());
			}
		}
		if(hits > 0)
		{
			totalHits += hits;
			color += weight * m_Color * brdf.Color() * (m_Area / hits);
		}
	}

	//additional shadow rays
	int hits = 0;
	int extraShadowSamples = c_LightSampleNum * 2;
	for(int i = 0; i < extraShadowSamples; i++)
	{
		double r0 = lameutil::g_RandGen.getDouble() - 0.5;
		double r1 = lameutil::g_RandGen.getDouble() - 0.5;

		Vec3 samplePoint = r0 * m_Edges[0] + r1 * m_Edges[1] + m_Pos;

		if(!scene.OcclusionTest(hitInfo.point, samplePoint))
		{
			hits++;
		}
	}
	totalHits += hits;
	totalSamples += extraShadowSamples;

	if(totalSamples > 0)
		color *= ((double)totalHits) / totalSamples;
		
}
