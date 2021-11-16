#include "HitablePdf.hpp"

float HitablePdf::Value(const Vector3 &direction) const
{
	return hitable->PdfValue(origin, direction);
}

Vector3 HitablePdf::Generate() const
{
	return hitable->Random(origin);
}