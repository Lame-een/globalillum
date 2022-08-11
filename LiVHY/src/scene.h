/// @file scene.h
#pragma once
#include <vector>
#include "util/types.h"
#include "util/colors.h"
#include "objects/light.h"
#include "objects/object.h"
#include "objects/triangleMesh.h"
#include "util/ray.h"
#include "objects/bvh.h"

/// @class Scene
/// @brief Class encapsulating the rendered scene.
class Scene : public Object{
public:
	Scene();
	~Scene();

	/// @brief Ray intersection checker function
	/// @param[in] ray Ray to check against
	/// @param[in] tMin Minimum ray length.
	/// @param[in] tMax Maximum ray length.
	/// @param[out] hitInfo Reference to the information about the hit.
	/// @return Returns true if the ray hit an object in the scene.
	bool Hit(const Ray& ray, double tMin, double tMax, HitInfo& hitInfo) override;
    /// @brief Constructs a bounding box around the objects.
    /// @param[out] outputBox The AABB of all the objects in the scene.
    /// @return Returns true if able to construct an AABB.
    bool BoundingBox(AABB& outputBox) const override;

	std::vector<Object*> Objects();
	std::vector<Light*> Lights();

	void AddObject(Object* obj);
	void AddObject(TriangleMesh* obj);
	void AddLight(Light* light);

	/// @brief Constructs a BVH around the encapsulated objects.
	void ConstructBvh();
	const BVHNode* BVHRoot() const;

	const RGB& Background() const;
	void SetBackground(const RGB& rgb);
private:
	RGB m_BackgroundColor = Colors::black;

	BVHNode* m_BVH = nullptr;
	std::vector<Object*> m_Objects;
	std::vector<Light*> m_Lights;
};