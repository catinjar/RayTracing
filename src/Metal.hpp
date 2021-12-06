#pragma once

#include <utility>

#include "Material.hpp"
#include "Texture.hpp"

class Metal : public Material
{
public:
	explicit Metal(std::shared_ptr<Texture> texture, float fuzziness) : texture(std::move(texture))
	{
		if (fuzziness < 1)
			this->fuzziness = fuzziness;
		else
			this->fuzziness = 1;
	}
	
	bool Scatter(const Ray &ray, const HitRecord &hitRecord, ScatterRecord &scatterRecord) const override;
	
	std::shared_ptr<Texture> texture;
	float fuzziness;
};