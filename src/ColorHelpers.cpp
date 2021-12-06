#include "ColorHelpers.hpp"

// Some samples might be NaN or a very big number and kill the whole pixel during the Monte-Carlo averaging
// We hide this issue here
Vector3 DeNan(const Vector3 &color)
{
	auto temp = color;
	
	if (temp.r != temp.r)
		temp.r = 0;
	
	if (temp.g != temp.g)
		temp.g = 0;
	
	if (temp.b != temp.b)
		temp.b = 0;
	
	return temp;
}

Vector3 GammaCorrect(const Vector3 &color)
{
	return { std::sqrt(color.r), std::sqrt(color.g), std::sqrt(color.b) };
}
