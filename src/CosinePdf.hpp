#pragma once

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