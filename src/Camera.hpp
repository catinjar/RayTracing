#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP


#include "Vector3.hpp"
#include "Ray.hpp"

class Camera
{
public:
	Camera() = default;
	Camera(const Vector3& lookFrom, const Vector3& lookAt, const Vector3& viewUp, float verticalFov, float aspect, float aperture, float focusDistance, float timeStart, float timeEnd);
	
	Ray GetRay(float s, float t) const;
	
	Vector3 origin {};
	Vector3 lowerLeft {};
	Vector3 horizontal {};
	Vector3 vertical {};
	
	Vector3 u {};
	Vector3 v {};
	Vector3 w {};
	
	float lensRadius = 0;
	float timeStart = 0;
	float timeEnd = 1;
};


#endif //RAYTRACER_CAMERA_HPP
