#pragma once

#include "Vector3.hpp"

class Pdf
{
public:
	virtual float Value(const Vector3 &direction) const = 0;
	virtual Vector3 Generate() const = 0;
};