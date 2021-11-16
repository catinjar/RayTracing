#include "FlipNormals.hpp"

bool FlipNormals::Hit(const Ray &ray, float minT, float maxT, HitRecord &hitRecord) const
{
	if (hitable->Hit(ray, minT, maxT, hitRecord))
	{
		hitRecord.normal = -hitRecord.normal;
		return true;
	}
	
	return false;
}

bool FlipNormals::BoundingBox(AABB &box, float timeStart, float timeEnd) const
{
	return hitable->BoundingBox(box, timeStart, timeEnd);
}
