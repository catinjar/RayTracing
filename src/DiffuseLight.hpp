#ifndef RAYTRACER_DIFFUSELIGHT_HPP
#define RAYTRACER_DIFFUSELIGHT_HPP


#include <utility>

#include "Material.hpp"
#include "Texture.hpp"

class DiffuseLight : public Material
{
public:
	explicit DiffuseLight(std::shared_ptr<Texture> texture) : texture(std::move(texture)) {}

	bool Scatter(const Ray &ray, const HitRecord &hitRecord, ScatterRecord &scatterRecord) const override;
	Vector3 Emitted(const Ray &ray, const HitRecord &hitRecord, float u, float v, const Vector3 &point) const override;

	std::shared_ptr<Texture> texture;
};


#endif //RAYTRACER_DIFFUSELIGHT_HPP
