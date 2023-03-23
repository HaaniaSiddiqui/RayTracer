#include "Whitted.hpp"
#include <iostream>
#include "../World/World.hpp"
#include "../Utilities/ShadeInfo.hpp"
#include "../Materials/Material.hpp"

Whitted::Whitted(World* world_ptr_)
{
    this->world_ptr = world_ptr_;
}

RGBColor Whitted::trace_ray(const Ray ray, const int depth) const{
    if(depth > world_ptr->vplane.max_depth){
        return black;
    }
    else {
        ShadeInfo sinfo(world_ptr->hit_objects(ray));
        if(sinfo.hit){
            sinfo.ray = ray;
            sinfo.depth = depth;
            return (sinfo.material_ptr->shade(sinfo));
        }
        else{
            return (world_ptr->bg_color);
        }
    }
}
