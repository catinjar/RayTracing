#include "MixturePdf.hpp"
#include "MathHelpers.hpp"

float MixturePdf::Value(const Vector3 &direction) const
{
	return 0.5f * pdfs[0]->Value(direction) + 0.5f * pdfs[1]->Value(direction);
}

Vector3 MixturePdf::Generate() const
{
	return Random01() < 0.5f
		? pdfs[0]->Generate()
		: pdfs[1]->Generate();
}
