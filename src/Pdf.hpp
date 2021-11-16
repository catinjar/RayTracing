#ifndef RAYTRACER_PDF_HPP
#define RAYTRACER_PDF_HPP


#include "Vector3.hpp"

class Pdf
{
public:
	virtual float Value(const Vector3 &direction) const = 0;
	virtual Vector3 Generate() const = 0;
};


#endif //RAYTRACER_PDF_HPP
