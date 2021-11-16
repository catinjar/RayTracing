#ifndef RAYTRACER_HITABLEPDF_HPP
#define RAYTRACER_HITABLEPDF_HPP


#include "Pdf.hpp"

#include <utility>
#include "Hitable.hpp"

class HitablePdf : public Pdf
{
public:
	HitablePdf(std::shared_ptr<Hitable> hitable, const Vector3 &origin) : hitable(std::move(hitable)), origin(origin) {}
	
	float Value(const Vector3 &direction) const override;
	
	Vector3 Generate() const override;
	
	std::shared_ptr<Hitable> hitable;
	Vector3 origin;
};


#endif //RAYTRACER_HITABLEPDF_HPP
