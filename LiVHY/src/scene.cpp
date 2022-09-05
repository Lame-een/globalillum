#include "pch.h"
#include "scene.h"

Scene::Scene()
	: m_Name(Settings::imgName), m_BackgroundColor(Settings::bgColor)
{
}Scene::Scene(const std::string& name)
	: m_Name(name)
{
}

Scene::~Scene()
{
	delete m_BVH;
}


//O(N) implementation which bruteforces the check against every object.
//bool Scene::Hit(const Ray& ray, double tMin, double tMax, HitInfo& hitInfo)
//{
//	hitInfo.t = std::numeric_limits<double>::max();
//	HitInfo auxInfo = hitInfo;
//	bool hit = false;
//	for(auto obj : m_Objects)
//	{
//		if(obj->Hit(ray, tMin, tMax, auxInfo) && auxInfo.t < hitInfo.t)
//		{
//			hitInfo = auxInfo;
//			hit = true;
//		}
//	}
//	return hit;
//}

/// The function uses the BVH to quickly check if the ray hits any objects in
/// the scene.
bool Scene::Hit(const Ray& ray, double tMin, double tMax, HitInfo& hitInfo) const
{
	return m_BVH->Hit(ray, tMin, tMax, hitInfo);
}

//bool Scene::BoundingBox(AABB& outputBox) const
//{
//	return false;
//};

const std::vector<Object*>& Scene::Objects() const
{
	return m_Objects;
}

const std::vector<Object*>& Scene::SamplingTargets() const
{
	return m_Targets;
}

void Scene::AddObject(Object* obj)
{
	m_Objects.push_back(obj);
	if(obj->GetMaterial()->IsEmissive() || obj->GetMaterial()->IsTransmissive() || obj->IsSamplingTarget()){
		AddSamplingTarget(obj);
	}
}

void Scene::AddObject(TriangleMesh* obj)
{
	m_Objects.insert(m_Objects.end(), obj->Triangles().begin(), obj->Triangles().end());
	if(obj->GetMaterial()->IsEmissive() || obj->GetMaterial()->IsTransmissive() || obj->IsSamplingTarget()){
		AddSamplingTarget(obj);
	}
}

void Scene::AddSamplingTarget(Object* tgt)
{
	m_Targets.push_back(tgt);
}

void Scene::AddSamplingTarget(TriangleMesh* tgt)
{
	m_Targets.insert(m_Targets.end(), tgt->Triangles().begin(), tgt->Triangles().end());
}

void Scene::ConstructBvh()
{
	delete m_BVH;
	m_BVH = new BVHNode(m_Objects, 0, m_Objects.size());
}

const BVHNode* Scene::BVHRoot() const
{
	return m_BVH;
}

const RGB& Scene::Background() const
{
	return m_BackgroundColor;
}

void Scene::SetBackground(const RGB& rgb)
{
	m_BackgroundColor = rgb;
}

Camera* Scene::Cam() const
{
	return m_Camera;
}

void Scene::SetCamera(Camera* cam)
{
	m_Camera = cam;
}

bool Scene::OcclusionTest(const Vec3& point, const Vec3& lightPoint) const
{
	double distToLight = glm::distance2(point, lightPoint);

	Ray occlusionRay(point, lightPoint - point);
	occlusionRay.Normalize();
	HitInfo occlusionHit;

	if(Hit(occlusionRay, Cam()->NearPlane(), distToLight, occlusionHit))
	{
		if((occlusionHit.t*occlusionHit.t < distToLight))
		{
			return true;
		}
	}
	
	return false;
}

const std::string& Scene::Name() const
{
	return m_Name;
}
