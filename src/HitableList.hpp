#pragma once

#include <utility>
#include <vector>
#include <memory>

#include "Hitable.hpp"

class HitableList : public Hitable
{
public:
	HitableList() = default;
	explicit HitableList(std::vector<std::shared_ptr<Hitable>> hitables) : hitables(std::move(hitables)) {}
	
	template<typename HitableType, typename... Args>
	void Add(Args&&... args)
	{
		hitables.push_back(std::make_shared<HitableType>(std::forward<Args>(args)...));
	}
	
	bool Hit(const Ray &ray, float minT, float maxT, HitRecord &hitRecord) const override;
	bool BoundingBox(AABB &box, float timeStart, float timeEnd) const override;
	
	float PdfValue(const Vector3 &origin, const Vector3 &direction) const override;
	Vector3 Random(const Vector3 &origin) const override;
	
private:
	std::vector<std::shared_ptr<Hitable>> hitables;
};