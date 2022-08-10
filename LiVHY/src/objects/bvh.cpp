#include "bvh.h"
#include <utility>
#include <functional>

#include <iostream>


//check for errors?
bool BoxCompare(int axis, Object* a, Object* b)
{
	AABB boxA, boxB;

	a->BoundingBox(boxA);
	b->BoundingBox(boxB);
	return boxA.Min()[axis] < boxB.Min()[axis];
}

BVHNode::~BVHNode(){
	delete dynamic_cast<BVHNode*>(m_Left); 
	delete dynamic_cast<BVHNode*>(m_Right); 
}

BVHNode::BVHNode(const std::vector<Object*>& Objects, size_t start, size_t end)
{
	std::vector<Object*> objects = Objects; //modifiable copy

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

	bool hitLeft = m_Left->Hit(ray, tMin, tMax, hitInfo);
	bool hitRight = m_Right->Hit(ray, tMin, hitLeft ? hitInfo.t : tMax, hitInfo);
	return hitLeft || hitRight;
}

bool BVHNode::BoundingBox(AABB& outputBox) const
{
	outputBox = m_BoundingBox;
	return true;
}

Object* BVHNode::Left()
{
	return m_Left;
}

Object* BVHNode::Right()
{
	return m_Right;
}