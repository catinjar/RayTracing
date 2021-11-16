#ifndef RAYTRACER_HITABLE_HPP
#define RAYTRACER_HITABLE_HPP


#include "Ray.hpp"
#include "HitRecord.hpp"
#include "AABB.hpp"

class Hitable
{
public:
	virtual bool Hit(const Ray& ray, float minT, float maxT, HitRecord& hitRecord) const = 0;
	virtual bool BoundingBox(AABB& box, float timeStart, float timeEnd) const = 0;
	
	virtual float PdfValue(const Vector3 &origin, const Vector3 &direction) const { return 0; }
	virtual Vector3 Random(const Vector3 &origin) const { return { 1, 0, 0 }; }
};


#endif //RAYTRACER_HITABLE_HPP
