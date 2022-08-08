#include "scene.h"

Scene::Scene()
{
}

bool Scene::Hit(const Ray& ray, const double& near, const double& far, HitInfo& hitInfo)
{
	hitInfo.t = std::numeric_limits<double>::max();
	HitInfo auxInfo = hitInfo;
	bool hit = false;
	for(auto obj : m_Objects)
	{
		if(obj->Hit(ray, near, far, auxInfo) && auxInfo.t < hitInfo.t)
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

const RGB& Scene::Background()
{
	return m_BackgroundColor;
}

void Scene::SetBackground(const RGB& rgb)
{
	m_BackgroundColor = rgb;
}
