#pragma once

#include "Tracer.hpp"

#define NULL __null

class AreaLighting : public Tracer {
public:
    AreaLighting(World* world_ptr_ = NULL);

	virtual RGBColor trace_ray(const Ray& ray) const;
	virtual RGBColor trace_ray(const Ray ray, const int depth) const;

};