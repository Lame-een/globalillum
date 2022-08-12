#include "bvh.h"
#include <utility>
#include <functional>

#include <iostream>

/// @class BVHNode
/// The binary tree is constructed in such a way that the
/// leaves are the objects in the scene.
/// When checking for ray intersects this should drastically 
/// reduce the amount of checks over the objects.

//TODO: add check for errors(?)
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

/// A recursive constructor which builds the hierarchy binary tree from
/// the passed dynamic array.
//TODO: add manual checks for array sizes of 2 and 3 for additional optimization
BVHNode::BVHNode(const std::vector<Object*>& objects, size_t start, size_t end)
{
	if(objects.size() == 0) return;
	std::vector<Object*> objs = objects; //create a modifiable copy

	int axis = m_RandGenerator.getInt(0, 2 + 1);
	size_t span = end - start;

	if(span == 1)	//doing a manual check for a single element
	{
		m_Left = m_Right = objs[start];
	}
	else{
		//bind has been shown to be more optimized than seperate functions
		std::sort(objs.begin() + start, objs.begin() + end, std::bind(BoxCompare, axis, std::placeholders::_1, std::placeholders::_2));

		size_t mid = start + span/2;	//split vector into 2 subarrays
		m_Left = new BVHNode(objs, start, mid);
		m_Right = new BVHNode(objs, mid, end);
	}

	AABB boxLeft, boxRight;
	//constructing the boundary box containing the children
	m_Left->BoundingBox(boxLeft);
	m_Right->BoundingBox(boxRight);
	
	boxLeft.Surround(boxRight);
	m_BoundingBox = boxLeft;
}

/// The optimized ray intersect function.
/// Only the leaves will do a complicated hit check as
/// they are the only "true objects".
bool BVHNode::Hit(const Ray& ray, double tMin, double tMax, HitInfo& hitInfo)
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