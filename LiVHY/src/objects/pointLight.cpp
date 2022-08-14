#include "pointLight.h"

PointLight::PointLight() : Light(LightType::Point)
{
}

PointLight::PointLight(const Vec3& pos, const RGB& color,
					   double intensity)
	: Light(pos, color, intensity, LightType::Point)
{
}

//RGB PointLight::Reflection(const BRDF& brdf, const HitInfo& hitInfo, const Vec3& origin) const
//{
//	return RGB();
//}

RGB PointLight::DiffuseReflection(const HitInfo& hitInfo) const
{
	const RGB& diffColor = hitInfo.object->Brdf()->Diffuse();

    double intensity = m_Intensity / glm::distance2(m_Pos, hitInfo.point);

    Vec3 l = glm::normalize(m_Pos - hitInfo.point); //vector towards the light
    double nl = glm::dot(hitInfo.normal, l);

    return (intensity * nl) * diffColor * m_Color;
}

RGB PointLight::SpecularReflection(const HitInfo& hitInfo) const
{
    const RGB& specularColor = hitInfo.object->Brdf()->Specular();
    const double& shininess = hitInfo.object->Brdf()->Shininess();

    double intensity = m_Intensity / glm::distance2(m_Pos, hitInfo.point);
    Vec3 l = glm::normalize(m_Pos - hitInfo.point); //vector towards the light
    double nl = glm::dot(hitInfo.normal, l);

#ifdef BLINN_PHONG
    ////blinn-phong
    //Vec3 h = glm::normalize(-hitInfo.ray.Dir()+ l);
    //double nh = glm::dot(hitInfo.normal,h);
    //if (nh < c_Epsilon) return Colors::black;

    //return (intensity * pow(nh,shininess) * specularColor * m_Color);
#else
    //phong reflectance
    Vec3 r = (2.0 * nl) * hitInfo.normal - l; //reflected light ray
    Vec3 v = -hitInfo.ray.Dir();    //vector towards eye
    double vr = glm::dot(v,r);
    if (vr < c_Epsilon) return Colors::black;
    
    return (intensity * pow(vr,shininess) * specularColor * m_Color);
#endif
}
