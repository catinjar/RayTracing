#ifndef RAYTRACER_SCENE_HPP
#define RAYTRACER_SCENE_HPP


#include <memory>

#include "Hitable.hpp"
#include "Camera.hpp"
#include "HitableList.hpp"

struct Scene
{
	int imageWidth;
	int imageHeight;
	int sampleCount;
	
	Camera camera;
	std::shared_ptr<Hitable> world;
	std::shared_ptr<HitableList> lightShape;
	
	inline std::size_t pixelCount() const { return imageWidth * imageHeight; }
	
	inline float aspectRatio() const { return float(imageWidth) / float(imageHeight); }
};

Scene CreateRandomScene();
Scene CreateCornellBoxScene();
Scene CreateAllFeaturesScene();

#endif //RAYTRACER_SCENE_HPP
