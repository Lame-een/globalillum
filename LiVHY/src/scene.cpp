#include "scene.h"

Scene::Scene()
{}

bool Scene::Intersects(const Ray & ray, Object*& hitObject, double& dist, Vec3& normal)
{
	dist = std::numeric_limits<double>::max();
	double auxDist = dist;
	Vec3 auxNorm;
	bool hit = false;
	for(auto obj : m_Objects)
	{
		if(obj->RayIntersect(ray, auxDist, auxNorm) && auxDist < dist)
		{
			hitObject = obj;
			dist = auxDist;
			normal = auxNorm;
			hit = true;
		}
	}
	return hit;
}

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
