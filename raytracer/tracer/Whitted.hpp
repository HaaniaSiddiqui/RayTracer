#pragma once

#include "Tracer.hpp"

#define NULL __null

class Whitted : public Tracer {
    public:
        Whitted(World* world_ptr_ = NULL);

        virtual RGBColor trace_ray(const Ray ray, const int depth) const;
};