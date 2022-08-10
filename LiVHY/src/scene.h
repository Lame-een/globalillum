#pragma once
#include <vector>
#include "util/types.h"
#include "util/colors.h"
#include "objects/light.h"
#include "objects/object.h"
#include "objects/triangleMesh.h"
#include "util/ray.h"
#include "objects/bvh.h"

class Scene : public Object{
public:
	Scene();
	~Scene();

	bool Hit(const Ray& ray, const double& tMin, const double& tMax, HitInfo& hitInfo) override;
    bool BoundingBox(AABB& output_box) const override;

	std::vector<Object*> Objects();
	std::vector<Light*> Lights();

	void AddObject(Object* obj);
	void AddObject(TriangleMesh* obj);
	void AddLight(Light* light);

	void ConstructBvh();
	const BVHNode* BVHRoot() const;

	const RGB& Background();
	void SetBackground(const RGB& rgb);
private:
	RGB m_BackgroundColor = Colors::black;

	BVHNode* m_BVH = nullptr;
	std::vector<Object*> m_Objects;
	std::vector<Light*> m_Lights;
};