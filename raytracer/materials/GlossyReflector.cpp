#include "GlossyReflector.hpp"
#include "../world/World.hpp"
#include "../tracer/Tracer.hpp"

// constructors, copy constructor
GlossyReflector::GlossyReflector() : Phong(), glossy_specular_brdf(new GlossySpecular) {}
GlossyReflector::GlossyReflector(const GlossyReflector &ref) : Phong(ref)
{
    if (ref.glossy_specular_brdf)
    {
        glossy_specular_brdf = ref.glossy_specular_brdf;
    }
    else
    {
        glossy_specular_brdf = new GlossySpecular;
    }
}

GlossyReflector &GlossyReflector::operator=(const GlossyReflector &ref)
{
    Phong::operator=(ref);
    if (ref.glossy_specular_brdf)
    {
        glossy_specular_brdf = ref.glossy_specular_brdf;
    }
    else
    {
        glossy_specular_brdf = new GlossySpecular;
    }

    return (*this);
}

// setter and getter functions
void GlossyReflector::set_samples(const int num_samples, const float exp)
{
    this->glossy_specular_brdf->set_samples(num_samples, exp);
}

void GlossyReflector::set_kr(const float k)
{
    if (glossy_specular_brdf)
    {
        glossy_specular_brdf->set_ks(k);
    }
}

void GlossyReflector::set_exp(const float exp)
{
    glossy_specular_brdf->set_exp(exp);
}

// set area light
RGBColor GlossyReflector::area_light_shade(ShadeInfo &sinfo)
{
    RGBColor L(Phong::area_light_shade(sinfo));
    Vector3D wo = -sinfo.ray.d;
    Vector3D wi;
    float pdf;
    RGBColor fr = this->glossy_specular_brdf->sample_f(sinfo, wo, wi, pdf);
    Ray reflective_ray(sinfo.hit_point, wi);

    L += fr * sinfo.w->tracer_ptr->trace_ray(reflective_ray, sinfo.depth + 1) * (sinfo.normal * wi) / pdf;

    return L;
}
