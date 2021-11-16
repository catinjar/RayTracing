#include "RotateY.hpp"

#include <numbers>

RotateY::RotateY(std::shared_ptr<Hitable> hitable, float angle) : hitable(std::move(hitable))
{
	const float radians = (float)std::numbers::pi / 180.0f * angle;
	
	sinTheta = std::sin(radians);
	cosTheta = std::cos(radians);
	
	hasBox = this->hitable->BoundingBox(boundingBox, 0, 1);
	
	Vector3 min(FLT_MAX, FLT_MAX, FLT_MAX);
	Vector3 max(FLT_MIN, FLT_MIN, FLT_MIN);
	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				float x = (float)i * boundingBox.max.x + (float)(1 - i) * boundingBox.min.x;
				float y = (float)j * boundingBox.max.x + (float)(1 - j) * boundingBox.min.y;
				float z = (float)k * boundingBox.max.x + (float)(1 - k) * boundingBox.min.z;
				
				float rotatedX = cosTheta * x + sinTheta * z;
				float rotatedZ = -sinTheta * x + cosTheta * z;
				
				Vector3 tester(rotatedX, y, rotatedZ);
				for (int axis = 0; axis < 3; axis++)
				{
					if (tester[axis] > max[axis])
						max[axis] = tester[axis];
					
					if (tester[axis] < min[axis])
						min[axis] = tester[axis];
				}
			}
		}
	}
	
	boundingBox = { min, max };
}

bool RotateY::Hit(const Ray &ray, float minT, float maxT, HitRecord &hitRecord) const
{
	Vector3 origin = ray.origin;
	Vector3 direction = ray.direction;
	
	origin[0] = cosTheta * ray.origin[0] - sinTheta * ray.origin[2];
	origin[2] = sinTheta * ray.origin[0] + cosTheta * ray.origin[2];
	
	direction[0] = cosTheta * ray.direction[0] - sinTheta * ray.direction[2];
	direction[2] = sinTheta * ray.direction[0] + cosTheta * ray.direction[2];
	
	Ray rotatedRay(origin, direction, ray.time);
	
	if (hitable->Hit(rotatedRay, minT, maxT, hitRecord))
	{
		Vector3 point = hitRecord.point;
		Vector3 normal = hitRecord.normal;
		
		point[0] = cosTheta * hitRecord.point[0] + sinTheta * hitRecord.point[2];
		point[2] = -sinTheta * hitRecord.point[0] + cosTheta * hitRecord.point[2];
		
		normal[0] = cosTheta * hitRecord.normal[0] + sinTheta * hitRecord.normal[2];
		normal[2] = -sinTheta * hitRecord.normal[0] + cosTheta * hitRecord.normal[2];
		
		hitRecord.point = point;
		hitRecord.normal = normal;
		
		return true;
	}
	
	return false;
}

bool RotateY::BoundingBox(AABB &box, float timeStart, float timeEnd) const
{
	box = boundingBox;
	return hasBox;
}