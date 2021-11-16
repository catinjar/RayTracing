#ifndef RAYTRACER_BOX_HPP
#define RAYTRACER_BOX_HPP


#include "HitableList.hpp"

class Box : public Hitable
{
public:
	Box(const Vector3 &min, const Vector3 &max, std::shared_ptr<Material> material);

	bool Hit(const Ray &ray, float minT, float maxT, HitRecord &hitRecord) const override;
	bool BoundingBox(AABB &box, float timeStart, float timeEnd) const override;

	Vector3 min;
	Vector3 max;
	HitableList sides;
};


#endif //RAYTRACER_BOX_HPP
