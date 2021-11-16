#include "CheckerTexture.hpp"

Vector3 CheckerTexture::Value(float u, float v, const Vector3 &point) const
{
	const float sines = std::sin(10 * point.x) * std::sin(10 * point.y) * std::sin(10 * point.z);
	
	return sines < 0
		? odd->Value(u, v, point)
		: even->Value(u, v, point);
}