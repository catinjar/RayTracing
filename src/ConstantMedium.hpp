#pragma once

#include "Hitable.hpp"
#include "Texture.hpp"

class ConstantMedium : public Hitable
{
public:
	ConstantMedium(std::shared_ptr<Hitable> hitable, float density, std::shared_ptr<Texture> texture);
	
	bool Hit(const Ray &ray, float minT, float maxT, HitRecord &hitRecord) const override;
	bool BoundingBox(AABB &box, float timeStart, float timeEnd) const override;
	
	float PdfValue(const Vector3 &origin, const Vector3 &direction) const override;
	Vector3 Random(const Vector3 &origin) const override;
	
	std::shared_ptr<Hitable> hitable;
	float density;
	std::shared_ptr<Material> phaseFunction;
};