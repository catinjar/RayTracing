#ifndef RAYTRACER_RECT_HPP
#define RAYTRACER_RECT_HPP


#include <utility>

#include "Hitable.hpp"
#include "MathHelpers.hpp"

template<int forwardAxisIndex, int rightAxisIndex, int upAxisIndex>
class Rect : public Hitable
{
public:
	Rect(float right0, float right1, float up0, float up1, float k, std::shared_ptr<Material> material)
		: right0(right0), right1(right1), up0(up0), up1(up1), k(k), material(std::move(material)) {};
	
	bool Hit(const Ray &ray, float minT, float maxT, HitRecord &hitRecord) const override
	{
		float t = (k - ray.origin[forwardAxisIndex]) / ray.direction[forwardAxisIndex];
		
		if (t < minT || t > maxT)
			return false;
		
		float right = ray.origin[rightAxisIndex] + t * ray.direction[rightAxisIndex];
		float up = ray.origin[upAxisIndex] + t * ray.direction[upAxisIndex];
		
		if (right < right0 || right > right1 || up < up0 || up > up1)
			return false;
		
		hitRecord.u = (right - right0) / (right1 - right0);
		hitRecord.v = (up - up0) / (up1 - up0);
		hitRecord.t = t;
		hitRecord.material = material.get();
		hitRecord.point = ray.GetPoint(t);
		hitRecord.normal = { 0, 0, 0 };
		hitRecord.normal[forwardAxisIndex] = 1;
		
		return true;
	}
	
	bool BoundingBox(AABB &box, float timeStart, float timeEnd) const override
	{
		box = { { right0, up0, k - 0.0001f }, { right1, up1, k + 0.0001f } };
		return true;
	}
	
	float PdfValue(const Vector3 &origin, const Vector3 &direction) const override
	{
		HitRecord hitRecord {};
		
		if (Hit({ origin, direction }, 0.001, FLT_MAX, hitRecord))
		{
			const float area = (right1 - right0) * (up1 - up0);
			const float distanceSquared = hitRecord.t * hitRecord.t * direction.SquaredLength();
			const float cosine = std::abs(Dot(direction, hitRecord.normal) / direction.Length());
			return distanceSquared / (cosine * area);
		}
		
		return 0;
	}
	
	Vector3 Random(const Vector3 &origin) const override
	{
		const Vector3 randomPoint(right0 + Random01() * (right1 - right0), k, up0 + Random01() * (up1 - up0));
		return randomPoint - origin;
	}
	
	float right0, right1, up0, up1, k;
	std::shared_ptr<Material> material;
};

class XYRect : public Rect<2, 0, 1>
{
public:
	XYRect(float right0, float right1, float up0, float up1, float k, std::shared_ptr<Material> material)
		: Rect<2, 0, 1>(right0, right1, up0, up1, k, std::move(material)) {}
};

class XZRect : public Rect<1, 0, 2>
{
public:
	XZRect(float right0, float right1, float up0, float up1, float k, std::shared_ptr<Material> material)
		: Rect<1, 0, 2>(right0, right1, up0, up1, k, std::move(material)) {}
};

class YZRect : public Rect<0, 1, 2>
{
public:
	YZRect(float right0, float right1, float up0, float up1, float k, std::shared_ptr<Material> material)
		: Rect<0, 1, 2>(right0, right1, up0, up1, k, std::move(material)) {}
};

#endif //RAYTRACER_RECT_HPP
