#include "HitableList.hpp"
#include "MathHelpers.hpp"

bool HitableList::Hit(const Ray &ray, float minT, float maxT, HitRecord& hitRecord) const
{
	HitRecord tempRecord {};
	bool hitAnything = false;
	float closest = maxT;
	
	for (auto&& hitable : hitables)
	{
		if (hitable->Hit(ray, minT, closest, tempRecord))
		{
			hitAnything = true;
			closest = tempRecord.t;
			hitRecord = tempRecord;
		}
	}
	
	return hitAnything;
}

bool HitableList::BoundingBox(AABB &box, float timeStart, float timeEnd) const
{
	if (hitables.empty())
		return false;
	
	AABB tempBox {};
	
	bool firstTrue = hitables[0]->BoundingBox(tempBox, timeStart, timeEnd);
	if (!firstTrue)
		return false;
	else
		box = tempBox;
	
	for (int i = 1; i < hitables.size(); i++)
	{
		if (hitables[i]->BoundingBox(tempBox, timeStart, timeEnd))
			box = SurroundingBox(box, tempBox);
		else
			return false;
	}
	
	return true;
}

float HitableList::PdfValue(const Vector3 &origin, const Vector3 &direction) const
{
	const float weight = 1.0f / (float)hitables.size();
	
	float sum = 0;
	for (const auto & hitable : hitables)
		sum += weight * hitable->PdfValue(origin, direction);
	
	return sum;
}

Vector3 HitableList::Random(const Vector3 &origin) const
{
	auto index = std::size_t(Random01() * (float)hitables.size());
	
	if (index == hitables.size())
		index = hitables.size() - 1;
	
	return hitables[index]->Random(origin);
}