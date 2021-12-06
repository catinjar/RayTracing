#pragma once

#include <vector>

#include "Hitable.hpp"

class BvhNode : public Hitable
{
public:
	BvhNode() = default;
	BvhNode(std::vector<std::shared_ptr<Hitable>>& hitables, int start, int end, float timeStart, float timeEnd);
	
	bool Hit(const Ray &ray, float minT, float maxT, HitRecord &hitRecord) const override;
	bool BoundingBox(AABB &box, float timeStart, float timeEnd) const override;
	
	std::shared_ptr<Hitable> left {};
	std::shared_ptr<Hitable> right {};
	
	AABB boundingBox {};
};