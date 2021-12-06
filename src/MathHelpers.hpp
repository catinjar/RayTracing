#pragma once

#include "Vector3.hpp"

float Random01();
Vector3 GetRandomPointInUnitSphere();
Vector3 GetRandomPointInUnitDisk();
Vector3 Reflect(const Vector3& vector, const Vector3& normal);
bool Refract(const Vector3& vector, const Vector3& normal, float refractiveIndexRatio, Vector3& refracted);
float Schlick(float cosine, float refractiveIndex);
float HermiteCubic(float value);
Vector3 GetRandomCosineDirection();