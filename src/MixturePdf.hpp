#pragma once

#include "Pdf.hpp"

#include <utility>

class MixturePdf : public Pdf
{
public:
	MixturePdf(const Pdf* pdf1, const Pdf* pdf2)
	{
		pdfs[0] = pdf1;
		pdfs[1] = pdf2;
	}
	
	float Value(const Vector3 &direction) const override;
	Vector3 Generate() const override;
	
	const Pdf* pdfs[2] {};
};