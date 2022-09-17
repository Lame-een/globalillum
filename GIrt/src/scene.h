/// @file scene.h
#pragma once
#include <vector>
#include "util/types.h"
#include "util/colors.h"
#include "objects/object.h"
#include "objects/triangleMesh.h"
#include "util/ray.h"
#include "objects/bvh.h"
#include "camera.h"
#include "cubemap.h"

/// @class Scene
/// @brief Class encapsulating the rendered scene.
class Scene{
public:
	Scene();
	Scene(const std::string& name);
	~Scene();

	/// @brief Ray intersection checker function
	/// @param[in] ray Ray to check against
	/// @param[in] tMin Minimum ray length.
	/// @param[in] tMax Maximum ray length.
	/// @param[out] hitInfo Reference to the information about the hit.
	/// @return Returns true if the ray hit an object in the scene.
	bool Hit(const Ray& ray, double tMin, double tMax, HitInfo& hitInfo) const;

    // @brief Constructs a bounding box around the objects.
    // @param[out] outputBox The AABB of all the objects in the scene.
    // @return Returns true if able to construct an AABB.
    //bool BoundingBox(AABB& outputBox) const override;

	const std::vector<Object*>& Objects() const;
	const std::vector<Object*>& SamplingTargets() const;

	void AddObject(Object* obj);
	void AddObject(TriangleMesh* obj);
	void AddSamplingTarget(Object* tgt);
	void AddSamplingTarget(TriangleMesh* tgt);

	/// @brief Constructs a BVH around the encapsulated objects.
	void ConstructBvh();
	const BVHNode* BVHRoot() const;

	RGB Background(const Vec3& dir) const;
	void SetBackground(const RGB& rgb);
	void SetBackground(const std::string& type);

	Camera* Cam() const;
	void SetCamera(Camera* cam);

	bool OcclusionTest(const Vec3& point, const Vec3& lightPoint) const;

	const std::string& Name() const;
private:
	bool m_BackgroundSolid = true;
	RGB m_BackgroundColor = Colors::black;
	CubeMap* m_CubeMap;

	Camera* m_Camera = nullptr;

	BVHNode* m_BVH = nullptr;
	std::vector<Object*> m_Objects;
	std::vector<Object*> m_Targets;

	std::string m_Name;
};