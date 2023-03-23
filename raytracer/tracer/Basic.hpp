#pragma once


#include "Tracer.hpp"

class World;
class RGBColor;

class Basic : public Tracer{
    public:
        Basic();
        Basic(World* world_ptr_);
        virtual RGBColor trace_ray(const Ray& ray) const;
        virtual ~Basic() = default;
};