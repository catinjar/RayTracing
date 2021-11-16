#ifndef RAYTRACER_LAMBERTIAN_HPP
#define RAYTRACER_LAMBERTIAN_HPP


#include <utility>

#include "Vector3.hpp"
#include "Material.hpp"
#include "Texture.hpp"

class Lambertian : public Material
{
public:
	explicit Lambertian(std::shared_ptr<Texture> texture) : texture(std::move(texture)) {}
	
	bool Scatter(const Ray &ray, const HitRecord &hitRecord, ScatterRecord &scatterRecord) const override;
	float ScatteringPdf(const Ray &ray, const HitRecord &hitRecord, const Ray &scattered) const override;
	
	std::shared_ptr<Texture> texture;
};


#endif //RAYTRACER_LAMBERTIAN_HPP
