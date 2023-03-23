#include "Matte.hpp"
#include <iostream>
#include "../World/World.hpp"
#include "../lights/Light.hpp"

// constructors
Matte::Matte(Lambertian *ambient_brdf_, Lambertian *diffuse_brdf_)
    : Material()
{
    if (ambient_brdf_ == NULL)
    {
        ambient_brdf = new Lambertian;
    }
    if (diffuse_brdf_ == NULL)
    {
        diffuse_brdf = new Lambertian;
    }
}

// copy constructor
Matte::Matte(const Matte &m) : Material(m)
{
    if (m.ambient_brdf)
    {
        ambient_brdf = m.ambient_brdf;
    }
    else
    {
        ambient_brdf = new Lambertian();
    }

    if (m.diffuse_brdf)
    {
        diffuse_brdf = m.diffuse_brdf;
    }
    else
    {
        diffuse_brdf = new Lambertian();
    }
}

// assignment operator
Matte &Matte::operator=(const Matte &matte)
{
    Material::operator=(matte);
    if (ambient_brdf && matte.ambient_brdf)
    {
        delete ambient_brdf;
        ambient_brdf = matte.ambient_brdf;
    }
    if (diffuse_brdf && matte.diffuse_brdf)
    {
        delete diffuse_brdf;
        diffuse_brdf = matte.diffuse_brdf;
    }

    return (*this);
}

// getter and setters
void Matte::set_ka(const float k)
{
    ambient_brdf->set_kd(k);
}

void Matte::set_kd(const float k)
{
    diffuse_brdf->set_kd(k);
}

void Matte::set_cd(const RGBColor &c)
{
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}

// ******************* get color funtions *******************
RGBColor Matte::shade(const ShadeInfo &sinfo) const
{
    Vector3D wo = -sinfo.ray.d;
    RGBColor L = ambient_brdf->rho(sinfo, wo) * sinfo.w->ambient_ptr->L(sinfo);
    int num_lights = sinfo.w->lights.size();

    for (int j = 0; j < num_lights; j++)
    {
        Vector3D wi = sinfo.w->lights[j]->get_direction(sinfo);
        float ndotwi = sinfo.normal * wi;

        if (ndotwi > 0.0)
        {
            bool in_shadow = false;
            if (sinfo.w->lights[j]->casts_shadows())
            {
                Ray shadowRay(sinfo.hit_point, wi);
                in_shadow = sinfo.w->lights[j]->in_shadow(shadowRay, sinfo);
            }
            if (!in_shadow)
            {
                L += diffuse_brdf->f(sinfo, wo, wi) * sinfo.w->lights[j]->L(sinfo) * ndotwi;
            }
        }
    }
    return L;
}

RGBColor Matte::area_light_shade(ShadeInfo &sinfo)
{
    Vector3D wo = -sinfo.ray.d;
    RGBColor L = ambient_brdf->rho(sinfo, wo) * sinfo.w->ambient_ptr->L(sinfo);
    int num_lights = sinfo.w->lights.size();

    for (int j = 0; j < num_lights; j++)
    {
        Vector3D wi = sinfo.w->lights[j]->get_direction(sinfo);
        float ndotwi = sinfo.normal * wi;
        if (ndotwi > 0.0)
        {
            bool in_shadow = false;
            if (sinfo.w->lights[j]->casts_shadows())
            {
                Ray shadowRay(sinfo.hit_point, wi);
                in_shadow = sinfo.w->lights[j]->in_shadow(shadowRay, sinfo);
            }
            if (!in_shadow)
            {
                L += diffuse_brdf->f(sinfo, wo, wi) * sinfo.w->lights[j]->L(sinfo) * sinfo.w->lights[j]->G(sinfo) * ndotwi /
                     sinfo.w->lights[j]->pdf(sinfo);
            }
        }
    }
    return L;
}
