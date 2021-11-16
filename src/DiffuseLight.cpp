#include "DiffuseLight.hpp"

bool DiffuseLight::Scatter(const Ray &ray, const HitRecord &hitRecord, ScatterRecord &scatterRecord) const
{
	return false;
}

Vector3 DiffuseLight::Emitted(const Ray &ray, const HitRecord &hitRecord, float u, float v, const Vector3 &point) const
{
	return Dot(hitRecord.normal, ray.direction) < 0
		? texture->Value(u, v, point)
		: Vector3(0, 0, 0);
}
