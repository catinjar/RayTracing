#ifndef RAYTRACER_TRANSLATE_HPP
#define RAYTRACER_TRANSLATE_HPP


#include "Hitable.hpp"

class Translate : public Hitable
{
public:
	Translate(std::shared_ptr<Hitable> hitable, const Vector3 &offset) : hitable(std::move(hitable)), offset(offset) {}
	
	bool Hit(const Ray &ray, float minT, float maxT, HitRecord &hitRecord) const override;
	bool BoundingBox(AABB &box, float timeStart, float timeEnd) const override;
	
	std::shared_ptr<Hitable> hitable;
	Vector3 offset;
};


#endif //RAYTRACER_TRANSLATE_HPP
