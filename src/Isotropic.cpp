#include "Isotropic.hpp"

#include <numbers>

#include "MathHelpers.hpp"

bool Isotropic::Scatter(const Ray &ray, const HitRecord &hitRecord, ScatterRecord &scatterRecord) const
{
	scatterRecord.isSpecular = true;
	scatterRecord.specularRay = { hitRecord.point, GetRandomPointInUnitSphere(), ray.time };
	scatterRecord.albedo = texture->Value(hitRecord.u, hitRecord.v, hitRecord.point);
	return true;
}

float Isotropic::ScatteringPdf(const Ray &ray, const HitRecord &hitRecord, const Ray &scattered) const
{
	return 1 / (4 * std::numbers::pi);
}
