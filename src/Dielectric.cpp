#include "Dielectric.hpp"
#include "MathHelpers.hpp"

bool Dielectric::Scatter(const Ray &ray, const HitRecord &hitRecord, ScatterRecord &scatterRecord) const
{
	scatterRecord.isSpecular = true;
	scatterRecord.albedo = { 1, 1, 1 };
	scatterRecord.pdf = nullptr;
	
	const auto reflected = Reflect(ray.direction, hitRecord.normal);
	
	Vector3 outwardNormal {};
	Vector3 refracted {};
	
	float refractiveIndexRatio;
	float cosine;
	
	if (Dot(ray.direction, hitRecord.normal) > 0)
	{
		outwardNormal = -hitRecord.normal;
		refractiveIndexRatio = refractiveIndex;
		cosine = Dot(ray.direction, hitRecord.normal) / ray.direction.Length();
		cosine = std::sqrt(1 - refractiveIndex * refractiveIndex * (1 - cosine * cosine));
	}
	else
	{
		outwardNormal = hitRecord.normal;
		refractiveIndexRatio = 1 / refractiveIndex;
		cosine = -Dot(ray.direction, hitRecord.normal) / ray.direction.Length();
	}
	
	const float reflectProbability = Refract(ray.direction, outwardNormal, refractiveIndexRatio, refracted)
		? Schlick(cosine, refractiveIndex)
		: 1;
	
	scatterRecord.specularRay = { hitRecord.point, Random01() < reflectProbability ? reflected : refracted, ray.time };
	
	return true;
}
