#ifndef RAYTRACER_SCATTERRECORD_H
#define RAYTRACER_SCATTERRECORD_H


#include "Ray.hpp"
#include "Pdf.hpp"

struct ScatterRecord
{
	Ray specularRay;
	bool isSpecular;
	Vector3 albedo;
	std::shared_ptr<Pdf> pdf;
};


#endif //RAYTRACER_SCATTERRECORD_H
