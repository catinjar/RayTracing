#include "ImageTexture.hpp"

#include <algorithm>

#include "ImageHelpers.hpp"

ImageTexture::ImageTexture(const char *filename)
{
	pixels = LoadPng(filename, width, height);
}

ImageTexture::~ImageTexture()
{
	delete[] pixels;
}

Vector3 ImageTexture::Value(float u, float v, const Vector3 &point) const
{
	int i = int(u * (float)width);
	int j = int((1 - v) * (float)height - 0.001);
	
	i = std::clamp(i, 0, width - 1);
	j = std::clamp(j, 0, height - 1);

	int offset = 3 * i + 3 * width * j;
	
	float r = (float)pixels[offset] / 255;
	float g = (float)pixels[offset + 1] / 255;
	float b = (float)pixels[offset + 2] / 255;
	
	return Vector3(r, g, b);
}
