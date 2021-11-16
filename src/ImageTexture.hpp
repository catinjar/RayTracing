#ifndef RAYTRACER_IMAGETEXTURE_HPP
#define RAYTRACER_IMAGETEXTURE_HPP


#include "Texture.hpp"

class ImageTexture : public Texture
{
public:
	explicit ImageTexture(const char* filename);
	virtual ~ImageTexture();
	
	Vector3 Value(float u, float v, const Vector3 &point) const override;
	
	int width = 0, height = 0;
	unsigned char* pixels;
};


#endif //RAYTRACER_IMAGETEXTURE_HPP
