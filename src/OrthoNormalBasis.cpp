#include "OrthoNormalBasis.hpp"

OrthoNormalBasis::OrthoNormalBasis(const Vector3 &n)
{
	w = n.Normalized();
	
	const auto a = std::abs(w.x) > 0.9
				   ? Vector3(0, 1, 0)
				   : Vector3(1, 0, 0);
	
	v = Cross(w, a).Normalized();
	u = Cross(w, v);
}
