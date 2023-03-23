#pragma once

/*
    Abstract class for inheriting different types of tracers    
*/

class RGBColor;
class World;
class Ray;

class Tracer {
    protected:
        World* world_ptr;

    public:
        Tracer();
        Tracer(World* world_ptr_);
        virtual RGBColor trace_ray(const Ray& ray) const;
        virtual RGBColor trace_ray(const Ray ray, const int depth) const;
        virtual ~Tracer() = default;
};
