#include "Metal.hpp"

#include "MathHelpers.hpp"

bool Metal::Scatter(const Ray &ray, const HitRecord &hitRecord, ScatterRecord &scatterRecord) const
{
	const auto reflected = Reflect(ray.direction.Normalized(), hitRecord.normal);
	scatterRecord.specularRay = { hitRecord.point, reflected + fuzziness * GetRandomPointInUnitSphere(), ray.time };
	scatterRecord.isSpecular = true;
	scatterRecord.albedo = texture->Value(hitRecord.u, hitRecord.v, hitRecord.point);
	scatterRecord.pdf = nullptr;
	return true;
}