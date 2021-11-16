#include "Lambertian.hpp"

#include <numbers>

#include "MathHelpers.hpp"
#include "OrthoNormalBasis.hpp"
#include "CosinePdf.hpp"

bool Lambertian::Scatter(const Ray &ray, const HitRecord &hitRecord, ScatterRecord &scatterRecord) const
{
	scatterRecord.isSpecular = false;
	scatterRecord.albedo = texture->Value(hitRecord.u, hitRecord.v, hitRecord.point);
	scatterRecord.pdf = std::make_shared<CosinePdf>(hitRecord.normal);
	return true;
}

float Lambertian::ScatteringPdf(const Ray &ray, const HitRecord &hitRecord, const Ray &scattered) const
{
	float cosine = Dot(hitRecord.normal, scattered.direction.Normalized());
	if (cosine < 0)
		cosine = 0;
	return cosine / std::numbers::pi;
}