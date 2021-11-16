#include "CosinePdf.hpp"

#include "MathHelpers.hpp"

#include <numbers>

CosinePdf::CosinePdf(const Vector3 &vector)
	: onb(vector) {}

float CosinePdf::Value(const Vector3 &direction) const
{
	const float cosine = Dot(direction.Normalized(), onb.w);
	
	return cosine > 0
		? cosine / (float)std::numbers::pi
		: 0;
}

Vector3 CosinePdf::Generate() const
{
	return onb.Local(GetRandomCosineDirection());
}
