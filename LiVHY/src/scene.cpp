#include "pch.h"
#include "scene.h"

Scene::Scene(const std::string& name)
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

const std::vector<Light*>& Scene::Lights() const
{
	return m_Lights;
}

void Scene::AddObject(Object* obj)
{
	m_Objects.push_back(obj);
}

void Scene::AddObject(TriangleMesh* obj)
{
	m_Objects.insert(m_Objects.end(), obj->Triangles().begin(), obj->Triangles().end());
}

void Scene::AddLight(Light* light)
{
	m_Lights.push_back(light);
}

void Scene::AddBrdf(BRDF* brdf)
{
	m_Brdfs.push_back(brdf);
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

const std::string& Scene::Name() const
{
	return m_Name;
}
