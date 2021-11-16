#include "Box.hpp"

#include "Rect.hpp"
#include "FlipNormals.hpp"

Box::Box(const Vector3 &min, const Vector3 &max, std::shared_ptr<Material> material)
	: min(min), max(max)
{
	sides.Add<XYRect>(min.x, max.x, min.y, max.y, max.z, material);
	sides.Add<FlipNormals>(std::make_shared<XYRect>(min.x, max.x, min.y, max.y, min.z, material));
	sides.Add<XZRect>(min.x, max.x, min.z, max.z, max.y, material);
	sides.Add<FlipNormals>(std::make_shared<XZRect>(min.x, max.x, min.z, max.z, min.y, material));
	sides.Add<YZRect>(min.y, max.y, min.z, max.z, max.x, material);
	sides.Add<FlipNormals>(std::make_shared<YZRect>(min.y, max.y, min.z, max.z, min.x, material));
}

bool Box::Hit(const Ray &ray, float minT, float maxT, HitRecord &hitRecord) const
{
	return sides.Hit(ray, minT, maxT, hitRecord);
}

bool Box::BoundingBox(AABB &box, float timeStart, float timeEnd) const
{
	box = { min, max };
	return true;
}