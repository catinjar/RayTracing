#include "NoiseTexture.hpp"

Vector3 NoiseTexture::Value(float u, float v, const Vector3 &point) const
{
	// return Vector3(1, 1, 1) * 0.5 * (1 + noise.Noise(scale * point)); // Common Perlin
	// return Vector3(1, 1, 1) * noise.Turbulence(scale * point); // Turbulence
	return Vector3(1, 1, 1) * 0.5 * (1 + std::sin(scale * point.z + 5 * noise.Turbulence(point))); // Marble
}
