#include "Sphere.hpp"
#include "OrthoNormalBasis.hpp"
#include "MathHelpers.hpp"

#include <numbers>

void GetSphereUV(const Vector3& point, float& u, float& v)
{
	const float phi = std::atan2(point.z, point.x);
	const float theta = std::asin(point.y);
	u = 1 - (phi + (float)std::numbers::pi) / (2 * (float)std::numbers::pi);
	v = (theta + (float)std::numbers::pi / 2) / (float)std::numbers::pi;
}

bool Sphere::Hit(const Ray &ray, float minT, float maxT, HitRecord &hitRecord) const
{
	const Vector3 originToCenter = ray.origin - Center(ray.time);
	
	const float a = Dot(ray.direction, ray.direction);
	const float b = 2 * Dot(originToCenter, ray.direction);
	const float c = Dot(originToCenter, originToCenter) - radius * radius;
	
	const float discriminant = b * b - 4 * a * c;
	
	if (discriminant < 0)
		return false;
	
	const auto center = Center(ray.time);
	
	float temp = (-b - std::sqrt(discriminant)) / (2 * a);
	if (temp > minT && temp < maxT)
	{
		
		hitRecord.t = temp;
		hitRecord.point = ray.GetPoint(hitRecord.t);
		hitRecord.normal = (hitRecord.point - center) / radius;
		hitRecord.material = material.get();
		GetSphereUV((hitRecord.point - center) / radius, hitRecord.u, hitRecord.v);
		return true;
	}
	
	temp = (-b + std::sqrt(discriminant)) / (2 * a);
	if (temp > minT && temp < maxT)
	{
		hitRecord.t = temp;
		hitRecord.point = ray.GetPoint(hitRecord.t);
		hitRecord.normal = (hitRecord.point - center) / radius;
		hitRecord.material = material.get();
		GetSphereUV((hitRecord.point - center) / radius, hitRecord.u, hitRecord.v);
		return true;
	}
	
	return false;
}

Vector3 Sphere::Center(float time) const
{
	return centerStart + (time - moveTimeStart) / (moveTimeEnd - moveTimeStart) * (centerEnd - centerStart);
}

bool Sphere::BoundingBox(AABB &box, float timeStart, float timeEnd) const
{
	const Vector3 radiusVector(radius, radius, radius);
	const AABB box1(centerStart - radiusVector, centerStart + radiusVector);
	const AABB box2(centerEnd - radiusVector, centerEnd + radiusVector);
	box = SurroundingBox(box1, box2);
	return true;
}

float Sphere::PdfValue(const Vector3 &origin, const Vector3 &direction) const
{
	HitRecord hitRecord {};
	
	if (Hit({ origin, direction}, 0.001, FLT_MAX, hitRecord))
	{
		const float cosThetaMax = std::sqrt(1 - radius * radius / (centerStart - origin).SquaredLength());
		const float solidAngle = 2 * std::numbers::pi * (1 - cosThetaMax);
		return 1 / solidAngle;
	}
	
	return 0;
}

Vector3 RandomToSphere(float radius, float distanceSquared)
{
	const float r1 = Random01();
	const float r2 = Random01();
	const float phi = 2 * std::numbers::pi * r1;
	
	const float z = 1 + r2 * (std::sqrt(1 - radius * radius / distanceSquared) - 1);
	const float x = std::cos(phi) * std::sqrt(1 - z * z);
	const float y = std::sin(phi) * std::sqrt(1 - z * z);
	
	return { x, y, z };
}

Vector3 Sphere::Random(const Vector3 &origin) const
{
	const auto direction = centerStart - origin;
	const float distanceSquared = direction.SquaredLength();
	
	OrthoNormalBasis onb(direction);
	return onb.Local(RandomToSphere(radius, distanceSquared));
}
