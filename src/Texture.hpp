#pragma once

#include "Vector3.hpp"

class Texture
{
public:
	virtual Vector3 Value(float u, float v, const Vector3& point) const = 0;
};