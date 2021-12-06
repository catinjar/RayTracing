#pragma once

#include "Hitable.hpp"

class RotateY : public Hitable
{
public:
	RotateY(std::shared_ptr<Hitable> hitable, float angle);
	
	bool Hit(const Ray &ray, float minT, float maxT, HitRecord &hitRecord) const override;
	
	bool BoundingBox(AABB &box, float timeStart, float timeEnd) const override;
	
	std::shared_ptr<Hitable> hitable;
	
	float sinTheta;
	float cosTheta;
	
	bool hasBox;
	AABB boundingBox {};
};