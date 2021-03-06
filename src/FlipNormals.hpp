#pragma once

#include "Hitable.hpp"

class FlipNormals : public Hitable
{
public:
	FlipNormals(std::shared_ptr<Hitable> hitable) : hitable(std::move(hitable)) {}
	
	bool Hit(const Ray &ray, float minT, float maxT, HitRecord &hitRecord) const override;
	bool BoundingBox(AABB &box, float timeStart, float timeEnd) const override;
	
	std::shared_ptr<Hitable> hitable;
};