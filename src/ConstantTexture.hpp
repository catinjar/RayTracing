#ifndef RAYTRACER_CONSTANTTEXTURE_HPP
#define RAYTRACER_CONSTANTTEXTURE_HPP


#include "Texture.hpp"

class ConstantTexture : public Texture
{
public:
	ConstantTexture() = default;
	explicit ConstantTexture(Vector3 color) : color(color) {}
	
	Vector3 Value(float u, float v, const Vector3& point) const override;
	
	Vector3 color {};
};


#endif //RAYTRACER_CONSTANTTEXTURE_HPP
