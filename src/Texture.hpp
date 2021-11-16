#ifndef RAYTRACER_TEXTURE_HPP
#define RAYTRACER_TEXTURE_HPP


#include "Vector3.hpp"

class Texture
{
public:
	virtual Vector3 Value(float u, float v, const Vector3& point) const = 0;
};


#endif //RAYTRACER_TEXTURE_HPP
