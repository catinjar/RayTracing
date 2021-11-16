#ifndef RAYTRACER_COSINEPDF_HPP
#define RAYTRACER_COSINEPDF_HPP


#include "Pdf.hpp"
#include "OrthoNormalBasis.hpp"

class CosinePdf : public Pdf
{
public:
	explicit CosinePdf(const Vector3 &vector);
	
	float Value(const Vector3 &direction) const override;
	Vector3 Generate() const override;
	
	OrthoNormalBasis onb;
};


#endif //RAYTRACER_COSINEPDF_HPP
