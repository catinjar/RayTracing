#pragma once

#include "Ray.hpp"
#include "Pdf.hpp"

struct ScatterRecord
{
	Ray specularRay;
	bool isSpecular;
	Vector3 albedo;
	std::shared_ptr<Pdf> pdf;
};