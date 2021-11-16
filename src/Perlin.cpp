#include "Perlin.hpp"

#include "MathHelpers.hpp"

Perlin::Perlin()
{
	randomVectors = GenerateVectors();
	xPermutation = GeneratePermutation();
	yPermutation = GeneratePermutation();
	zPermutation = GeneratePermutation();
}

float PerlinTrilinearInterpolation(const Vector3 corners[2][2][2], float u, float v, float w)
{
	const float uu = HermiteCubic(u);
	const float vv = HermiteCubic(v);
	const float ww = HermiteCubic(w);
	
	float sum = 0;
	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				const Vector3 weight(u - (float)i, v - (float)j, w - (float)k);
				sum += ((float)i * uu + (float)(1 - i) * (1 - uu)) *
					   ((float)j * vv + (float)(1 - j) * (1 - vv)) *
					   ((float)k * ww + (float)(1 - k) * (1 - ww)) * Dot(corners[i][j][k], weight);
			}
		}
	}
	
	return sum;
}

float Perlin::Noise(const Vector3 &point) const
{
	float u = point.x - std::floor(point.x);
	float v = point.y - std::floor(point.y);
	float w = point.z - std::floor(point.z);
	
	int i = std::floor(point.x);
	int j = std::floor(point.y);
	int k = std::floor(point.z);
	
	Vector3 corners[2][2][2];
	for (int di = 0; di < 2; di++)
	{
		for (int dj = 0; dj < 2; dj++)
		{
			for (int dk = 0; dk < 2; dk++)
				corners[di][dj][dk] = randomVectors[xPermutation[(i + di) & 255] ^ yPermutation[(j + dj) & 255] ^ zPermutation[(k + dk) & 255]];
		}
	}
	
	return PerlinTrilinearInterpolation(corners, u, v, w);
}

float Perlin::Turbulence(const Vector3 &point, int depth) const
{
	float sum = 0;
	
	Vector3 tempPoint = point;
	float weight = 1;
	
	for (int i = 0; i < depth; i++)
	{
		sum += weight * Noise(tempPoint);
		weight *= 0.5;
		tempPoint *= 2;
	}
	
	return std::abs(sum);
}

std::vector<Vector3> Perlin::GenerateVectors()
{
	randomVectors.reserve(256);

	for (int i = 0; i < 256; i++)
		randomVectors.emplace_back(Vector3(-1 + 2 * Random01(), -1 + 2 * Random01(), -1 + 2 * Random01()).Normalized());
	
	return randomVectors;
}

void Permute(std::vector<int> &permutation)
{
	for (std::size_t i = permutation.size() - 1; i > 0; i--)
	{
		int target = int(Random01() * (float)(i + 1));
		int tmp = permutation[i];
		permutation[i] = permutation[target];
		permutation[target] = tmp;
	}
}

std::vector<int> Perlin::GeneratePermutation()
{
	std::vector<int> permutation;
	permutation.reserve(256);
	
	for (int i = 0; i < 256; i++)
		permutation.push_back(i);
	
	Permute(permutation);
	
	return permutation;
}
