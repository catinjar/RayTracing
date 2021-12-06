#pragma once

#include "Vector3.hpp"
#include "Ray.hpp"

class AABB
{
public:
	AABB() = default;
	AABB(const Vector3& min, const Vector3& max) : min(min), max(max) {}
	
	bool Hit(const Ray& ray, float minT, float maxT) const;
	
	Vector3 min;
	Vector3 max;
};

AABB SurroundingBox(const AABB& box1, const AABB& box2);