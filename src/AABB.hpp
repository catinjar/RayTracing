#ifndef RAYTRACER_AABB_HPP
#define RAYTRACER_AABB_HPP


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

AABB SurroundingBox(AABB box1, AABB box2);

#endif //RAYTRACER_AABB_HPP
