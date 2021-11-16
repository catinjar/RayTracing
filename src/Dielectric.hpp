#ifndef RAYTRACER_DIELECTRIC_HPP
#define RAYTRACER_DIELECTRIC_HPP


#include "Material.hpp"

class Dielectric : public Material
{
public:
	explicit Dielectric(float refractiveIndex) : refractiveIndex(refractiveIndex) {}
	
	bool Scatter(const Ray &ray, const HitRecord &hitRecord, ScatterRecord &scatterRecord) const override;
	
	float refractiveIndex;
};


#endif //RAYTRACER_DIELECTRIC_HPP
