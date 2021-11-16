#ifndef RAYTRACER_MATERIAL_HPP
#define RAYTRACER_MATERIAL_HPP


#include "Ray.hpp"
#include "HitRecord.hpp"
#include "ScatterRecord.h"

class Material
{
public:
	virtual bool Scatter(const Ray& ray, const HitRecord& hitRecord, ScatterRecord &scatterRecord) const { return false; }
	virtual float ScatteringPdf(const Ray &ray, const HitRecord &hitRecord, const Ray &scattered) const { return 0; }
	virtual Vector3 Emitted(const Ray &ray, const HitRecord &hitRecord, float u, float v, const Vector3 &point) const { return {0, 0, 0}; }
};


#endif //RAYTRACER_MATERIAL_HPP
