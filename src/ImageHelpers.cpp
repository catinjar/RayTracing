#include "ImageHelpers.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../third_party/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../third_party/stb_image_write.h"

unsigned char* LoadPng(const char* filename, int &width, int &height)
{
	int channels;
	return stbi_load(filename, &width, &height, &channels, 3);
}

void SavePng(const char* filename, int width, int height, const std::vector<Vector3> &pixels)
{
	auto* image = new unsigned char[3 * width * height];
	
	for (int i = 0; i < pixels.size(); i++)
	{
		image[3 * i] = std::min(255, int(255 * pixels[i].r));
		image[3 * i + 1] = std::min(255, int(255 * pixels[i].g));
		image[3 * i + 2] = std::min(255, int(255 * pixels[i].b));
	}
	
	stbi_write_png(filename, width, height, 3, image, width * 3);
	
	delete[] image;
}