#ifndef RAYTRACER_ORTHONORMALBASIS_HPP
#define RAYTRACER_ORTHONORMALBASIS_HPP


#include "Vector3.hpp"

class OrthoNormalBasis
{
public:
	explicit OrthoNormalBasis(const Vector3 &n);
	
	Vector3 Local(const Vector3 &a) const { return a.x * u + a.y * v + a.z * w; }
	
	Vector3 u;
	Vector3 v;
	Vector3 w;
};


#endif //RAYTRACER_ORTHONORMALBASIS_HPP
