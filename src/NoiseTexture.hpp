#ifndef RAYTRACER_NOISETEXTURE_HPP
#define RAYTRACER_NOISETEXTURE_HPP


#include "Texture.hpp"
#include "Perlin.hpp"

class NoiseTexture : public Texture
{
public:
	explicit NoiseTexture(float scale) : scale(scale) {}
	
	Vector3 Value(float u, float v, const Vector3 &point) const override;
	
	Perlin noise {};
	float scale;
};


#endif //RAYTRACER_NOISETEXTURE_HPP
