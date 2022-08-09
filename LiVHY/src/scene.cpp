#include "scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	delete m_BVH;
}

/*
bool Scene::Hit(const Ray& ray, const double& tMin, const double& tMax, HitInfo& hitInfo)
{
	hitInfo.t = std::numeric_limits<double>::max();
	HitInfo auxInfo = hitInfo;
	bool hit = false;
	for(auto obj : m_Objects)
	{
		if(obj->Hit(ray, tMin, tMax, auxInfo) && auxInfo.t < hitInfo.t)
		{
			hitInfo = auxInfo;
			hit = true;
		}
	}
	return hit;
}
*/

bool Scene::Hit(const Ray& ray, const double& tMin, const double& tMax, HitInfo& hitInfo)
{
	return m_BVH->Hit(ray, tMin, tMax, hitInfo);

	hitInfo.t = std::numeric_limits<double>::max();
	HitInfo auxInfo = hitInfo;
	bool hit = false;
	for(auto obj : m_Objects)
	{
		if(obj->Hit(ray, tMin, tMax, auxInfo) && auxInfo.t < hitInfo.t)
		{
			hitInfo = auxInfo;
			hit = true;
		}
	}
	return hit;
}

bool Scene::BoundingBox(AABB& output_box) const
{
	return false;
};

std::vector<Object*> Scene::Objects()
{
	return m_Objects;
}

std::vector<Light*> Scene::Lights()
{
	return m_Lights;
}

void Scene::AddObject(Object* obj)
{
	m_Objects.push_back(obj);
}

void Scene::AddLight(Light* light)
{
	m_Lights.push_back(light);
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

const RGB& Scene::Background()
{
	return m_BackgroundColor;
}

void Scene::SetBackground(const RGB& rgb)
{
	m_BackgroundColor = rgb;
}
