#include "MathHelpers.hpp"

#include <random>
#include <numbers>

std::random_device randomDevice;
std::mt19937 gen(randomDevice());
std::uniform_real_distribution<float> dis;

float Random01()
{
	return dis(gen);
}

Vector3 GetRandomPointInUnitSphere()
{
	Vector3 point {};
	
	do
	{
		point = 2 * Vector3(Random01(), Random01(), Random01()) - Vector3(1, 1, 1);
	} while (point.SquaredLength() >= 1);
	
	return point;
}

Vector3 GetRandomPointInUnitDisk()
{
	Vector3 point {};
	
	do
	{
		point = 2 * Vector3(Random01(), Random01(), 0) - Vector3(1, 1, 0);
	} while (Dot(point, point) >= 1);
	
	return point;
}

Vector3 Reflect(const Vector3& vector, const Vector3& normal)
{
	return vector - 2 * Dot(vector, normal) * normal;
}

bool Refract(const Vector3& vector, const Vector3& normal, float refractiveIndexRatio, Vector3& refracted)
{
	const Vector3 uv = vector.Normalized();
	const float dt = Dot(uv, normal);
	const float discriminant = 1 - refractiveIndexRatio * refractiveIndexRatio * (1 - dt * dt);
	
	if (discriminant > 0)
	{
		refracted = refractiveIndexRatio * (uv - normal * dt) - normal * std::sqrt(discriminant);
		return true;
	}
	
	return false;
}

float Schlick(float cosine, float refractiveIndex)
{
	float r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
	r0 = r0 * r0;
	return r0 + (1 - r0) * (float)std::pow(1 - cosine, 5);
}

float HermiteCubic(float value)
{
	return value * value * (3 - 2 * value);
}

Vector3 GetRandomCosineDirection()
{
	const float r1 = Random01();
	const float r2 = Random01();
	const float phi = 2 * std::numbers::pi * r1;
	
	const float x = std::cos(phi) * 2 * std::sqrt(r2);
	const float y = std::sin(phi) * 2 * std::sqrt(r2);
	const float z = std::sqrt(1 - r2);
	
	return { x, y, z };
}