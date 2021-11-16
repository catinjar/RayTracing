#ifndef RAYTRACER_CHECKERTEXTURE_HPP
#define RAYTRACER_CHECKERTEXTURE_HPP


#include <utility>

#include "Texture.hpp"

class CheckerTexture : public Texture
{
public:
	CheckerTexture() = default;
	CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd) : odd(std::move(odd)), even(std::move(even)) {}
	
	Vector3 Value(float u, float v, const Vector3 &point) const override;
	
	std::shared_ptr<Texture> even;
	std::shared_ptr<Texture> odd;
};


#endif //RAYTRACER_CHECKERTEXTURE_HPP
