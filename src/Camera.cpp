#include "Camera.hpp"

#include <numbers>

#include "MathHelpers.hpp"

Camera::Camera(const Vector3& lookFrom, const Vector3& lookAt, const Vector3& viewUp, float verticalFov, float aspect, float aperture, float focusDistance, float timeStart, float timeEnd)
{
	const float theta = verticalFov * (float)std::numbers::pi / 180;
	const float halfHeight = std::tan(theta / 2);
	const float halfWidth = aspect * halfHeight;
	
	origin = lookFrom;
	
	w = (lookFrom - lookAt).Normalized();
	u = Cross(viewUp, w).Normalized();
	v = Cross(w, u);
	
	lowerLeft = origin - halfWidth * focusDistance * u - halfHeight * focusDistance * v - focusDistance * w;
	horizontal = 2 * halfWidth * focusDistance * u;
	vertical = 2 * halfHeight * focusDistance * v;
	
	lensRadius = aperture / 2;
	
	this->timeStart = timeStart;
	this->timeEnd = timeEnd;
}

Ray Camera::GetRay(float s, float t) const
{
	const auto randomPoint = lensRadius * GetRandomPointInUnitDisk();
	const auto offset = u * randomPoint.x + v * randomPoint.y;
	const float time = timeStart + Random01() * (timeEnd - timeStart);
	return { origin + offset, lowerLeft + s * horizontal + t * vertical - origin - offset, time };
}
