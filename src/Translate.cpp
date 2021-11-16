#include "Translate.hpp"

bool Translate::Hit(const Ray &ray, float minT, float maxT, HitRecord &hitRecord) const
{
	Ray movedRay(ray.origin - offset, ray.direction, ray.time);
	
	if (hitable->Hit(movedRay, minT, maxT, hitRecord))
	{
		hitRecord.point += offset;
		return true;
	}
	
	return false;
}

bool Translate::BoundingBox(AABB &box, float timeStart, float timeEnd) const
{
	if (hitable->BoundingBox(box, timeStart, timeEnd))
	{
		box = { box.min + offset, box.max + offset };
		return true;
	}
	
	return false;
}
