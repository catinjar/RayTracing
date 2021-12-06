#pragma once

#include "Material.hpp"

class Dielectric : public Material
{
public:
	explicit Dielectric(float refractiveIndex) : refractiveIndex(refractiveIndex) {}
	
	bool Scatter(const Ray &ray, const HitRecord &hitRecord, ScatterRecord &scatterRecord) const override;
	
	float refractiveIndex;
};