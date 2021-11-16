#include "ConstantTexture.hpp"

Vector3 ConstantTexture::Value(float u, float v, const Vector3& point) const
{
	return color;
}