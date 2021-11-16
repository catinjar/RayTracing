#ifndef RAYTRACER_IMAGEHELPERS_HPP
#define RAYTRACER_IMAGEHELPERS_HPP


#include <vector>

#include "Vector3.hpp"

unsigned char* LoadPng(const char* filename, int &width, int &height);
void SavePng(const char* filename, int width, int height, const std::vector<Vector3> &pixels);


#endif //RAYTRACER_IMAGEHELPERS_HPP
