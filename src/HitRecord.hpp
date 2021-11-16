#ifndef RAYTRACER_HITRECORD_HPP
#define RAYTRACER_HITRECORD_HPP


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


#endif //RAYTRACER_HITRECORD_HPP
