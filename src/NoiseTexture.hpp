#pragma once

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