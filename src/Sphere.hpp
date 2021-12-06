#pragma once

#include <utility>

#include "Hitable.hpp"

class Sphere : public Hitable
{
public:
	Sphere(const Vector3& centerStart, const Vector3& centerEnd, float timeStart, float timeEnd, float radius, std::shared_ptr<Material> material)
		: centerStart(centerStart), centerEnd(centerEnd), moveTimeStart(timeStart), moveTimeEnd(timeEnd), radius(radius), material(std::move(material)) {}
	
	Sphere(const Vector3 center, float radius, std::shared_ptr<Material> material)
		: centerStart(center), centerEnd(center), radius(radius), material(std::move(material)), moveTimeStart(0), moveTimeEnd(1) {}
	
	bool Hit(const Ray &ray, float minT, float maxT, HitRecord& hitRecord) const override;
	bool BoundingBox(AABB &box, float timeStart, float timeEnd) const override;
	
	float PdfValue(const Vector3 &origin, const Vector3 &direction) const override;
	Vector3 Random(const Vector3 &origin) const override;
	
	Vector3 Center(float time) const;
	
	Vector3 centerStart;
	Vector3 centerEnd;
	
	float radius;
	std::shared_ptr<Material> material;
	
	float moveTimeStart;
	float moveTimeEnd;
};
