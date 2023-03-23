#include "Tracer.hpp"
#include <iostream>
#include "../utilities/Ray.hpp"
#include "../utilities/RGBColor.hpp"

Tracer::Tracer(): world_ptr(NULL)
{}

Tracer::Tracer(World* world_ptr_):world_ptr(world_ptr_)
{}

RGBColor Tracer::trace_ray(const Ray ray, const int depth) const {
    return RGBColor(0);
}

RGBColor Tracer::trace_ray(const Ray& ray) const {
    return RGBColor(0);
}