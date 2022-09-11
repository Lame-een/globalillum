/// @file objects/bvh.h
#pragma once
#include <vector>
#include "object.h"
#include "lame/easyRandom.h"

/// @brief Comparison function used by std::sort.
/// @param[in] axis Axis on which to sort.
/// @param[in] a Pointer to object A.
/// @param[in] b Pointer to object B.
/// @return Returns true if object A is smaller than B on the passed axis.
bool BoxCompare(int axis, Object* a, Object* b);

/// @class BVHNode
/// @brief Class implementing a Bounding Volume Hierarchy node.
class BVHNode : public Object{
public:
	/// @brief Constructor for a single node.
	/// @param[in] objects Dynamic array containing all the objects in the hierarchy.
	/// @param[in] start Start index of the subarray contained in the node.
	/// @param[in] end End index of the subarray contained in the node.
	BVHNode(const std::vector<Object*>& objects, size_t start, size_t end);
	~BVHNode();

	/// @brief Ray intersection checker function for the node.
	/// @param[in] ray The cast ray.
	/// @param[in] tMin Minimum length of the ray.
	/// @param[in] tMax Maximum length of the ray.
	/// @param[out] hitInfo Reference to the information about the hit.
	/// @return Returns true if the ray hit the node.
	bool Hit(const Ray& ray, float tMin, float tMax, HitInfo& hitInfo) const override;
	/// @brief Constructs a bounding box around the node.
    /// @param[out] outputBox The AABB of the node.
    /// @return Returns true if able to construct an AABB.
    bool BoundingBox(AABB& outputBox) const override;

	Object* Left();
	Object* Right();

private:
	Object* m_Left = nullptr;
	Object* m_Right = nullptr;
	AABB m_BoundingBox;

	lameutil::EasyRandom m_RandGenerator;
};