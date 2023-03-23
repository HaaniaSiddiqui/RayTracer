#include "RayCast.hpp"
#include "../World/World.hpp"
#include "../Utilities/ShadeInfo.hpp"
#include "../Materials/Material.hpp"

RayCast::RayCast(World* world_ptr_r):
    Tracer(world_ptr_r)
{}

RGBColor RayCast::trace_ray(const Ray& ray) const{
    ShadeInfo sinfo(world_ptr->hit_objects(ray));

    if(sinfo.hit)
    {
        sinfo.ray = ray;
        return (sinfo.material_ptr->shade(sinfo));
    }
    else
    {
        return (world_ptr->bg_color);
    }
}

RGBColor RayCast::trace_ray(const Ray ray, const int depth) const{
    ShadeInfo sinfo(world_ptr->hit_objects(ray));

    if(sinfo.hit)
    {
        sinfo.ray = ray;
        return (sinfo.material_ptr->shade(sinfo));
    }
    else
    {
        return (world_ptr->bg_color);
    }
}
