#include "BvhNode.hpp"

#include <iostream>
#include <algorithm>

#include "MathHelpers.hpp"

template<int axis>
struct BoxCompare
{
	bool operator()(const std::shared_ptr<Hitable>& left, const std::shared_ptr<Hitable>& right)
	{
		AABB boxLeft {};
		AABB boxRight {};
		
		if (!left->BoundingBox(boxLeft, 0, 0) || !right->BoundingBox(boxRight, 0, 0))
			std::cerr << "No bounding box in BvhNode constructor" << std::endl;
		
		return boxLeft.min[axis] < boxRight.min[axis];
	}
};

BvhNode::BvhNode(std::vector<std::shared_ptr<Hitable>>& hitables, int start, int end, float timeStart, float timeEnd)
{
	const int sortAxis = int(3 * Random01());
	
	switch (sortAxis)
	{
		case 0:
			std::sort(hitables.begin() + start, hitables.begin() + end, BoxCompare<0>());
			break;
		
		case 1:
			std::sort(hitables.begin() + start, hitables.begin() + end, BoxCompare<1>());
			break;
		
		default:
			std::sort(hitables.begin() + start, hitables.begin() + end, BoxCompare<2>());
			break;
	}
	
	const std::size_t count = end - start;
	
	if (count == 1)
	{
		left = right = hitables[start];
	}
	else if (count == 2)
	{
		left = hitables[start];
		right = hitables[start + 1];
	}
	else
	{
		left = std::make_shared<BvhNode>(hitables, start, start + (end - start) / 2, timeStart, timeEnd);
		right = std::make_shared<BvhNode>(hitables , start + (end - start) / 2, end, timeStart, timeEnd);
	}
	
	AABB boxLeft {};
	AABB boxRight {};
	
	if (!left->BoundingBox(boxLeft, timeStart, timeEnd) || !right->BoundingBox(boxRight, timeStart, timeEnd))
		std::cerr << "No bounding box in BvhNode constructor" << std::endl;
	
	boundingBox = SurroundingBox(boxLeft, boxRight);
}

bool BvhNode::Hit(const Ray &ray, float minT, float maxT, HitRecord &hitRecord) const
{
	if (boundingBox.Hit(ray, minT, maxT))
	{
		HitRecord leftHitRecord {};
		HitRecord rightHitRecord {};
		
		bool hitLeft = left->Hit(ray, minT, maxT, leftHitRecord);
		bool hitRight = right->Hit(ray, minT, maxT, rightHitRecord);
		
		if (hitLeft && hitRight)
		{
			hitRecord = leftHitRecord.t < rightHitRecord.t ? leftHitRecord : rightHitRecord;
			return true;
		}
		else if (hitLeft)
		{
			hitRecord = leftHitRecord;
			return true;
		}
		else if (hitRight)
		{
			hitRecord = rightHitRecord;
			return true;
		}
		else
		{
			return false;
		}
	}
	
	return false;
}

bool BvhNode::BoundingBox(AABB &box, float timeStart, float timeEnd) const
{
	box = boundingBox;
	return true;
}