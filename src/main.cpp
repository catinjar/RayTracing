#include <chrono>
#include <iostream>
#include <future>

#include "Vector3.hpp"
#include "Ray.hpp"
#include "Hitable.hpp"
#include "Camera.hpp"
#include "Material.hpp"
#include "MathHelpers.hpp"
#include "ImageHelpers.hpp"
#include "Scene.hpp"
#include "HitablePdf.hpp"
#include "MixturePdf.hpp"
#include "ColorHelpers.h"

Vector3 GetScreenColor(const Ray& ray, const std::shared_ptr<Hitable>& world, const std::shared_ptr<Hitable>& importanceSamplingShape, int depth = 50)
{
	if (depth <= 0)
		return { 0, 0, 0 };

	HitRecord hitRecord {};
	
	if (!world->Hit(ray, 0.001f, FLT_MAX, hitRecord))
		return { 0, 0, 0 };
	
	ScatterRecord scatterRecord;
	
	const auto emitted = hitRecord.material->Emitted(ray, hitRecord, hitRecord.u, hitRecord.v, hitRecord.point);
	
	if (!hitRecord.material->Scatter(ray, hitRecord, scatterRecord))
		return emitted;
	
	if (scatterRecord.isSpecular)
		return scatterRecord.albedo * GetScreenColor(scatterRecord.specularRay, world, importanceSamplingShape, depth - 1);
	
	Ray scattered {};
	float pdf;
	
	if (importanceSamplingShape != nullptr)
	{
		const HitablePdf importanceSamplingPdf(importanceSamplingShape, hitRecord.point);
		const MixturePdf mixturePdf(&importanceSamplingPdf, scatterRecord.pdf.get());
		
		scattered = { hitRecord.point, mixturePdf.Generate(), ray.time };
		pdf = mixturePdf.Value(scattered.direction);
	}
	else
	{
		scattered = { hitRecord.point, scatterRecord.pdf->Generate(), ray.time };
		pdf = scatterRecord.pdf->Value(scattered.direction);
	}
	
	return emitted
		+ scatterRecord.albedo
		* hitRecord.material->ScatteringPdf(ray, hitRecord, scattered)
		* GetScreenColor(scattered, world, importanceSamplingShape, depth + 1)
		/ pdf;
}

int main()
{
	const auto scene = CreateAllFeaturesScene();
	const std::size_t pixelCount = scene.pixelCount();
	
	const auto startTime = std::chrono::high_resolution_clock::now();
	
	std::vector<Vector3> pixels;
	pixels.resize(pixelCount);
	
	const std::size_t coreCount = std::thread::hardware_concurrency();
	std::vector<std::future<void>> futures;
	
	for (std::size_t coreIndex = 0; coreIndex < coreCount; coreIndex++)
	{
		futures.emplace_back(std::async([&scene, &pixels, pixelCount, coreCount, coreIndex]
		{
			for (std::size_t pixelIndex = coreIndex; pixelIndex < pixelCount; pixelIndex += coreCount)
			{
				const std::size_t x = pixelIndex % scene.imageWidth;
				const std::size_t y = pixelIndex / scene.imageWidth;
				
				Vector3 color {};
				
				for (int sampleIndex = 0; sampleIndex < scene.sampleCount; sampleIndex++)
				{
					float u = float((float)x + Random01()) / float(scene.imageWidth);
					float v = float((float)y + Random01()) / float(scene.imageHeight);
					
					const auto ray = scene.camera.GetRay(u, v);
					
					color += GetScreenColor(ray, scene.world, scene.lightShape);
				}
				
				color = DeNan(color);
				color /= float(scene.sampleCount);
				color = GammaCorrect(color);
				
				const std::size_t offset = (scene.imageHeight - y - 1) * scene.imageWidth + x;
				pixels[offset] = color;
			}
		}));
	}
	
	for (const auto& future : futures)
		future.wait();
	
	SavePng("output.png", scene.imageWidth, scene.imageHeight, pixels);
	
	const auto endTime = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<float> durationInSeconds = endTime - startTime;
	std::cout << durationInSeconds.count() << std::endl;
	
	return 0;
}
