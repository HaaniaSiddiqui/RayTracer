#include "Basic.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"
#include "../materials/Material.hpp"

Basic::Basic() {
    this->world_ptr = nullptr;
}

Basic::Basic(World* world_ptr_) {
    this->world_ptr = world_ptr_;
}

RGBColor Basic::trace_ray(const Ray& ray) const {
    ShadeInfo sinfo = world_ptr->hit_objects(ray);
    if (sinfo.hit)
    {
        return ray.w * sinfo.material_ptr->shade(sinfo);
    }
	else
    {
        return ray.w * world_ptr->bg_color;
    }
}
