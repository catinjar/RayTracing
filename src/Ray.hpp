#ifndef RAYTRACER_RAY_HPP
#define RAYTRACER_RAY_HPP


#include "Vector3.hpp"

struct Ray
{
	Ray() = default;
	Ray(const Vector3& origin, const Vector3& direction, float time = 0) : origin(origin), direction(direction), time(time) {}
	
	Vector3 GetPoint(float t) const { return origin + t * direction; }
	
	Vector3 origin;
	Vector3 direction;
	
	float time;
};


#endif //RAYTRACER_RAY_HPP
