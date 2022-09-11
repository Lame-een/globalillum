/// @file objects/object.h
#pragma once
#include "util/types.h"
#include "util/ray.h"
#include "aabb.h"
#include "util/hitInfo.h"
#include "material.h"

/// @class Object
/// @brief Base class for all objects.
class Object
{
public:
	Object(bool cull = true, bool samplingTarget = false);
	Object(const Material* mat, bool cull = true, bool samplingTarget = false);

	/// @brief Ray intersection checker function.
	/// @param[in] ray Ray to check against.
	/// @param[in] tMin Minimum ray length.
	/// @param[in] tMax Maximum ray length.
	/// @param[out] hitInfo Reference to the information about the hit.
	/// @return Returns true if the ray hit the object.
	virtual bool Hit(const Ray& ray, double tMin, double tMax, HitInfo& hitInfo) const;
	/// @brief Constructs a bounding box around the object.
	/// @param[out] outputBox The AABB of the object.
	/// @return Returns true if able to construct an AABB.
	virtual bool BoundingBox(AABB& outputBox) const;

	virtual Vec3 Random(Vec3 point) const;
	virtual double PdfValue(const Vec3& origin, const Vec3& dir) const;

	bool IsSamplingTarget() const;

	const Material* GetMaterial() const;
protected:
	const Material* m_Mat = nullptr;

	bool m_Cull;
	bool m_SamplingTarget;
};