#include "AABB.hpp"

bool AABB::Hit(const Ray &ray, float minT, float maxT) const
{
	for (int axisIndex = 0; axisIndex < 3; axisIndex++)
	{
		float inversedDirection = 1 / ray.direction[axisIndex];
		
		float t0 = (min[axisIndex] - ray.origin[axisIndex]) * inversedDirection;
		float t1 = (max[axisIndex] - ray.origin[axisIndex]) * inversedDirection;
		
		if (inversedDirection < 0)
			std::swap(t0, t1);
		
		minT = t0 > minT ? t0 : minT;
		maxT = t1 < maxT ? t1 : maxT;
		
		if (maxT <= minT)
			return false;
	}
	
	return true;
}

AABB SurroundingBox(AABB box1, AABB box2)
{
	const Vector3 min(std::min(box1.min.x, box2.min.x), std::min(box1.min.y, box2.min.y), std::min(box1.min.z, box2.min.z));
	const Vector3 max(std::max(box1.max.x, box2.max.x), std::max(box1.max.y, box2.max.y), std::max(box1.max.z, box2.max.z));
	return { min, max };
}
