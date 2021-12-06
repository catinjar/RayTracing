#pragma once

#include "Vector3.hpp"

class Material;

struct HitRecord
{
	float t;
	Vector3 point;
	Vector3 normal;
	Material* material;
	float u;
	float v;
};