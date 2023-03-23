#pragma once 

#define NULL __null

#include "Tracer.hpp"

class RayCast: public Tracer{
    public:
        RayCast(World* world_ptr_ = NULL);

        virtual RGBColor trace_ray(const Ray& ray) const;
        virtual RGBColor trace_ray(const Ray ray, const int depth) const;
};