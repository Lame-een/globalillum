#include "bvh.h"
#include <utility>
#include <functional>


//check for errors?
bool BoxCompare(int axis, Hittable* a, Hittable* b)
{
	AABB boxA, boxB;

	a->BoundingBox(boxA);
	b->BoundingBox(boxB);
	return boxA.Min()[axis] < boxB.Min()[axis];

}

BVHNode::BVHNode(const HittableList& list)
	: BVHNode(list.List(), 0, list.List().size())
{
}

//look into optimizing this further
//-maybe manually check for 2 and 3 objects inside list to avoid
//	unnecessary function calls
//-remove the bindings?
BVHNode::BVHNode(const std::vector<Hittable*>& hittables, size_t start, size_t end)
{
	std::vector<Hittable*> objects = hittables; //modifiable copy

	int axis = m_RandGenerator.getInt(0, 2 + 1);
	size_t span = end - start;

	if(span == 1)
	{
		m_Left = m_Right = objects[start];
	}
	else{
		std::sort(objects.begin() + start, objects.begin() + end, std::bind(BoxCompare, axis, std::placeholders::_1, std::placeholders::_2));

		size_t mid = start + span/2;
		m_Left = new BVHNode(objects, start, mid);
		m_Right = new BVHNode(objects, mid, end);
	}

	AABB boxLeft, boxRight;
	m_Left->BoundingBox(boxLeft);
	m_Right->BoundingBox(boxRight);
	
	boxLeft.Surround(boxRight);
	m_BoundingBox = boxLeft;
}

bool BVHNode::Hit(const Ray& ray, const double& tMin, const double& tMax, HitInfo& hitInfo)
{
	if(!m_BoundingBox.Hit(ray, tMin, tMax)) return false;

	return m_Left->Hit(ray, tMin, tMax, hitInfo) ||
		m_Right->Hit(ray, tMin, tMax, hitInfo);

	//bool hitLeft = m_Left->Hit(ray, tMin, tMax, hitInfo);
	//bool hitRight = m_Right->Hit(ray, hitLeft ? hitInfo.t : tMin, tMax, hitInfo);
	//return hitLeft || hitRight;
}

bool BVHNode::BoundingBox(AABB& outputBox) const
{
	outputBox = m_BoundingBox;
	return true;
}

Hittable* BVHNode::Left()
{
	return m_Left;
}

Hittable* BVHNode::Right()
{
	return m_Right;
}