#ifndef RAYTRACER_COLORHELPERS_H
#define RAYTRACER_COLORHELPERS_H


#include "Vector3.hpp"

Vector3 DeNan(const Vector3 &color);
Vector3 GammaCorrect(const Vector3 &color);

#endif //RAYTRACER_COLORHELPERS_H
