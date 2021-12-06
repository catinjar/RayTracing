#pragma once

#include <vector>
#include "Vector3.hpp"

class Perlin
{
public:
	Perlin();
	
	float Noise(const Vector3& point) const;
	float Turbulence(const Vector3& point, int depth = 7) const;
	
	std::vector<Vector3> randomVectors;
	std::vector<int> xPermutation;
	std::vector<int> yPermutation;
	std::vector<int> zPermutation;
	
private:
	std::vector<Vector3> GenerateVectors();
	static std::vector<int> GeneratePermutation();
};