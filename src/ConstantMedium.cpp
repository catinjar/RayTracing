#include "ConstantMedium.hpp"

#include <utility>

#include "Isotropic.hpp"
#include "MathHelpers.hpp"

ConstantMedium::ConstantMedium(std::shared_ptr<Hitable> hitable, float density, std::shared_ptr<Texture> texture)
	: hitable(std::move(hitable)), density(density)
{
	phaseFunction = std::make_shared<Isotropic>(std::move(texture));
}

bool ConstantMedium::Hit(const Ray &ray, float minT, float maxT, HitRecord &hitRecord) const
{
	HitRecord hitRecord1 {};
	HitRecord hitRecord2 {};
	
	if (hitable->Hit(ray, FLT_MIN, FLT_MAX, hitRecord1))
	{
		if (hitable->Hit(ray, hitRecord1.t + 0.0001f, FLT_MAX, hitRecord2))
		{
			if (hitRecord1.t < minT)
				hitRecord1.t = minT;
			
			if (hitRecord2.t > maxT)
				hitRecord2.t = maxT;
			
			if (hitRecord1.t >= hitRecord2.t)
				return false;
			
			if (hitRecord1.t < 0)
				hitRecord1.t = 0;
			
			const float distanceInsideBoundary = (hitRecord2.t - hitRecord1.t) * ray.direction.Length();
			const float hitDistance = -(1 / density) * std::log(Random01());
			
			if (hitDistance < distanceInsideBoundary)
			{
				hitRecord.t = hitRecord1.t + hitDistance / ray.direction.Length();
				hitRecord.point = ray.GetPoint(hitRecord.t);
				hitRecord.normal = Vector3(1, 0, 0); // Arbitrary
				hitRecord.material = phaseFunction.get();
				return true;
			}
		}
	}
	
	return false;
}

bool ConstantMedium::BoundingBox(AABB &box, float timeStart, float timeEnd) const
{
	return hitable->BoundingBox(box, timeStart, timeEnd);
}

float ConstantMedium::PdfValue(const Vector3 &origin, const Vector3 &direction) const
{
	return hitable->PdfValue(origin, direction);
}

Vector3 ConstantMedium::Random(const Vector3 &origin) const
{
	return hitable->Random(origin);
}
