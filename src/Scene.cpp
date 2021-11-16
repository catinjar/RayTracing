#include "Scene.hpp"

#include <vector>

#include "Sphere.hpp"
#include "Lambertian.hpp"
#include "ConstantTexture.hpp"
#include "CheckerTexture.hpp"
#include "Dielectric.hpp"
#include "ImageTexture.hpp"
#include "NoiseTexture.hpp"
#include "MathHelpers.hpp"
#include "DiffuseLight.hpp"
#include "Metal.hpp"
#include "BvhNode.hpp"
#include "Rect.hpp"
#include "FlipNormals.hpp"
#include "Box.hpp"
#include "Translate.hpp"
#include "RotateY.hpp"
#include "ConstantMedium.hpp"

Scene CreateRandomScene()
{
	Scene scene;
	
	scene.imageWidth = 300;
	scene.imageHeight = 300;
	scene.sampleCount = 100;
	
	const Vector3 lookFrom = { 13, 2, 3 };
	const Vector3 lookAt = { 0, 0, 0 };
	const Vector3 up = { 0, 1, 0 };
	const float distanceToFocus = 10;
	const float aperture = 0.1;
	const float verticalFov = 20;
	
	scene.camera = Camera(lookFrom, lookAt, up, verticalFov, scene.aspectRatio(), aperture, distanceToFocus, 0, 1);

	std::vector<std::shared_ptr<Hitable>> hitables;
	
	hitables.push_back(std::make_shared<Sphere>(Vector3(0, -1000, 0), 1000,
												std::make_shared<Lambertian>(std::make_shared<CheckerTexture>(
													std::make_shared<ConstantTexture>(Vector3(0.2, 0.3, 0.1)),
													std::make_shared<ConstantTexture>(Vector3(0.9, 0.9, 0.9))))));
	
	hitables.push_back(std::make_shared<Sphere>(Vector3(0, 1, 0), 1, std::make_shared<Dielectric>(1.5)));
	hitables.push_back(std::make_shared<Sphere>(Vector3(-4, 1, 0), 1, std::make_shared<Lambertian>(std::make_shared<NoiseTexture>(10))));
	hitables.push_back(std::make_shared<Sphere>(Vector3(4, 1, 0), 1, std::make_shared<Lambertian>(std::make_shared<ImageTexture>("../textures/earth.png"))));
	
	for (int x = -11; x < 11; x++)
	{
		for (int z = -11; z < 11; z++)
		{
			const float randomMaterial = Random01();
			const Vector3 center((float)x + 0.9f * Random01(), 0.2, (float)z + Random01());
			
			if ((center - Vector3(4, 0.2, 0)).Length() > 0.9)
			{
				if (randomMaterial < 0.8)
					hitables.push_back(std::make_shared<Sphere>(center, center + Vector3(0, 0, 0), 0, 1, 0.2,
																std::make_shared<DiffuseLight>(std::make_shared<ConstantTexture>(Vector3(Random01() * Random01(), Random01() * Random01(), Random01() * Random01())))));
				else if (randomMaterial < 0.95)
					hitables.push_back(std::make_shared<Sphere>(center, 0.2,
																std::make_shared<Metal>(std::make_shared<ConstantTexture>(Vector3(0.5f * (1 + Random01()), 0.5f * (1 + Random01()), 0.5f * (1 + Random01()))), 0.5f * Random01())));
				else
					hitables.push_back(std::make_shared<Sphere>(center, 0.2,
																std::make_shared<Dielectric>(1.5)));
			}
		}
	}
	
	scene.world = std::make_shared<BvhNode>(hitables, 0, hitables.size(), 0, 1);
	
	return scene;
}

Scene CreateCornellBoxScene()
{
	Scene scene;
	
	scene.imageWidth = 300;
	scene.imageHeight = 300;
	scene.sampleCount = 100;
	
	const Vector3 lookFrom = { 278, 278, -800 };
	const Vector3 lookAt = { 278, 278, 0 };
	const Vector3 up = { 0, 1, 0 };
	const float distanceToFocus = 10;
	const float aperture = 0;
	const float verticalFov = 40;
	
	scene.camera = Camera(lookFrom, lookAt, up, verticalFov, scene.aspectRatio(), aperture, distanceToFocus, 0, 1);
	
	auto hitableList = std::make_shared<HitableList>();
	
	const auto red = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(Vector3(0.65, 0.05, 0.05)));
	const auto white = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(Vector3(0.73, 0.73, 0.73)));
	const auto green = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(Vector3(0.12, 0.45, 0.15)));
	const auto light = std::make_shared<DiffuseLight>(std::make_shared<ConstantTexture>(Vector3(15, 15, 15)));
	const auto glass = std::make_shared<Dielectric>(1.5f);
	
	hitableList->Add<FlipNormals>(std::make_shared<YZRect>(0, 555, 0, 555, 555, green));
	hitableList->Add<YZRect>(0, 555, 0, 555, 0, red);
	hitableList->Add<FlipNormals>(std::make_shared<XZRect>(213, 343, 227, 332, 554, light));
	hitableList->Add<FlipNormals>(std::make_shared<XZRect>(0, 555, 0, 555, 555, white));
	hitableList->Add<XZRect>(0, 555, 0, 555, 0, white);
	hitableList->Add<FlipNormals>(std::make_shared<XYRect>(0, 555, 0, 555, 555, white));
	
	hitableList->Add<Sphere>(Vector3(190, 90, 190), 90, glass);
	hitableList->Add<Translate>(std::make_shared<RotateY>(std::make_shared<Box>(Vector3(0, 0.01, 0), Vector3(165, 330,165), white), 15), Vector3(265, 0, 295));
	
	scene.world = std::move(hitableList);
	
	auto lightShape = std::make_shared<HitableList>();
	lightShape->Add<XZRect>(213, 343, 227, 332, 554, nullptr);
	lightShape->Add<Sphere>(Vector3(190, 90, 190), 90, nullptr);
	
	scene.lightShape = std::move(lightShape);
	
	return scene;
}

Scene CreateAllFeaturesScene()
{
	Scene scene;
	
	scene.imageWidth = 300;
	scene.imageHeight = 300;
	scene.sampleCount = 100;
	
	const Vector3 lookFrom = { 478, 278, -600 };
	const Vector3 lookAt = { 278, 278, 0 };
	const Vector3 up = { 0, 1, 0 };
	const float distanceToFocus = 10;
	const float aperture = 0;
	const float verticalFov = 40;

	scene.camera = Camera(lookFrom, lookAt, up, verticalFov, scene.aspectRatio(), aperture, distanceToFocus, 0, 1);
	
	auto hitableList = std::make_shared<HitableList>();
	
	const auto ground = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(Vector3(0.48, 0.83, 0.53)));

	std::vector<std::shared_ptr<Hitable>> boxes;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			const float offset = 100;

			const float x0 = -1000 + (float)i * offset;
			const float z0 = -1000 + (float)j * offset;
			const float y0 = 0;

			const float x1 = x0 + offset;
			const float y1 = 100.0f * (Random01() + 0.01f);
			const float z1 = z0 + offset;

			boxes.push_back(std::make_shared<Box>(Vector3(x0, y0, z0), Vector3(x1, y1, z1), ground));
		}
	}

	hitableList->Add<BvhNode>(boxes, 0, boxes.size(), 0, 1);

	const auto light = std::make_shared<DiffuseLight>(std::make_shared<ConstantTexture>(Vector3(7, 7, 7)));
	hitableList->Add<FlipNormals>(std::make_shared<XZRect>(123, 423, 147, 412, 554, light));

	const Vector3 center(400, 400, 200);
	hitableList->Add<Sphere>(center, center + Vector3(30, 0, 0), 0, 1, 50,
							 std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(Vector3(0.7, 0.3, 0.1))));

	hitableList->Add<Sphere>(Vector3(260, 150, 45), 50, std::make_shared<Dielectric>(1.5));
	hitableList->Add<Sphere>(Vector3(0, 150, 45), 50, std::make_shared<Metal>(std::make_shared<ConstantTexture>(Vector3(0.8, 0.8, 0.9)), 10));

	hitableList->Add<Sphere>(Vector3(360, 150, 145), 70, std::make_shared<Dielectric>(1.5));
	hitableList->Add<ConstantMedium>(std::make_shared<Sphere>(Vector3(360, 150, 145), 69.99f,
															  std::make_shared<Dielectric>(1.5)), 0.2, std::make_shared<ConstantTexture>(Vector3(0.2, 0.4, 0.9)));

	hitableList->Add<ConstantMedium>(std::make_shared<Sphere>(Vector3(0, 0, 0), 5000,
															  std::make_shared<Dielectric>(1.5)), 0.001f, std::make_shared<ConstantTexture>(Vector3(1, 1, 1)));

	hitableList->Add<Sphere>(Vector3(400, 200, 400), 100, std::make_shared<Lambertian>(std::make_shared<ImageTexture>("../textures/earth.png")));
	hitableList->Add<Sphere>(Vector3(220, 280, 300), 80, std::make_shared<Lambertian>(std::make_shared<NoiseTexture>(0.1)));

	const auto white = std::make_shared<Lambertian>(std::make_shared<ConstantTexture>(Vector3(0.73, 0.73, 0.73)));

	std::vector<std::shared_ptr<Hitable>> spheres;
	spheres.reserve(250);
	for (int i = 0; i < 250; i++)
		spheres.push_back(std::make_shared<Sphere>(Vector3(165 * Random01(), 165 * Random01(), 165 * Random01()), 10, white));

	hitableList->Add<Translate>(std::make_shared<RotateY>(std::make_shared<BvhNode>(spheres, 0, spheres.size(), 0, 1), 15), Vector3(-100, 270, 395));
	
	scene.world = std::move(hitableList);
	
	return scene;
}