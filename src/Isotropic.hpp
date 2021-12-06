#pragma once

#include <utility>

#include "Material.hpp"
#include "Texture.hpp"

class Isotropic : public Material
{
public:
	explicit Isotropic(std::shared_ptr<Texture> texture) : texture(std::move(texture)) {}
	
	bool Scatter(const Ray &ray, const HitRecord &hitRecord, ScatterRecord &scatterRecord) const override;
	float ScatteringPdf(const Ray &ray, const HitRecord &hitRecord, const Ray &scattered) const override;
	
	std::shared_ptr<Texture> texture;
};