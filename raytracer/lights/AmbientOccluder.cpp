#include "AmbientOccluder.hpp"
#include "../samplers/Simple.hpp"
#include "../Utilities/ShadeInfo.hpp"
#include "../World/World.hpp"
#include "../geometry/Geometry.hpp"

AmbientOccluder::AmbientOccluder()
    : u(0), v(0), w(0), sampler_ptr(new Simple()) {}

AmbientOccluder::AmbientOccluder(const AmbientOccluder &ambient)
    : u(ambient.u), v(ambient.v), w(ambient.w)
{
    if (ambient.sampler_ptr)
    {
        sampler_ptr = ambient.sampler_ptr;
    }
    else
    {
        sampler_ptr = new Simple();
    }
}

AmbientOccluder &AmbientOccluder::operator=(const AmbientOccluder &ambient)
{
    Light::operator=(ambient);
    u = ambient.u;
    v = ambient.v;
    w = ambient.w;
    if (ambient.sampler_ptr)
    {
        sampler_ptr = ambient.sampler_ptr;
    }
    else
    {
        sampler_ptr = new Simple();
    }

    return (*this);
}

void AmbientOccluder::set_sampler(Sampler *s_ptr)
{
}

Vector3D AmbientOccluder::get_direction(ShadeInfo &sinfo)
{
    return Vector3D(0.0);
}

bool AmbientOccluder::in_shadow(const Ray &ray, const ShadeInfo &sinfo) const
{
    float t;
    int num_objects = sinfo.w->geometry.size();
    for (int j = 0; j < num_objects; j++)
    {
        if (sinfo.w->geometry[j]->shadow_hit(ray, t))
        {
            return true;
        }
    }
    return false;
}

RGBColor AmbientOccluder::L(ShadeInfo &sinfo)
{
    w = sinfo.normal;
    v = w ^ Vector3D(0.00072, 1.0, 0.0034);
    v.normalize();
    u = v ^ w;
    Ray shadow_ray;
    shadow_ray.o = sinfo.hit_point;
    shadow_ray.d = get_direction(sinfo);

    if (in_shadow(shadow_ray, sinfo))
    {
        return (min_amount * ls * color);
    }
    else
    {
        return (ls * color);
    }
}
