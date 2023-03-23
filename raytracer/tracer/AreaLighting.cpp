#include "AreaLighting.hpp"
#include <iostream>
#include "../World/World.hpp"
#include "../Utilities/ShadeInfo.hpp"
#include "../Materials/Material.hpp"

AreaLighting::AreaLighting(World* world_ptr_r):Tracer(world_ptr_r){}

RGBColor AreaLighting::trace_ray(const Ray& ray) const{
    ShadeInfo sinfo(world_ptr->hit_objects(ray));
    if(sinfo.hit)
    {
        sinfo.ray = ray;
        return (sinfo.material_ptr->area_light_shade(sinfo));
    }
    else
    {
        return (world_ptr->bg_color);
    }
}

RGBColor AreaLighting::trace_ray(const Ray ray, const int depth) const{
    ShadeInfo sinfo(world_ptr->hit_objects(ray));

    if(sinfo.hit)
    {
        sinfo.ray = ray;
        return (sinfo.material_ptr->area_light_shade(sinfo));
    }
    else
    {
        return (world_ptr->bg_color);
    }
}
