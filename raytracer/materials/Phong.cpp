#include "Phong.hpp"
#include <iostream>
#include "../World/World.hpp"
#include "../lights/Light.hpp"

// constructors

Phong::Phong(Lambertian *ambient_brdf_, Lambertian *diffuse_brdf_, GlossySpecular *specular_brdf_) : Material()
{
    ambient_brdf = ambient_brdf_;
    diffuse_brdf = diffuse_brdf_;
    specular_brdf = specular_brdf_;
    if (ambient_brdf_ == NULL)
    {
        ambient_brdf = new Lambertian;
    }
    if (diffuse_brdf_ == NULL)
    {
        diffuse_brdf = new Lambertian;
    }
    if (specular_brdf_ == NULL)
    {
        specular_brdf = new GlossySpecular;
    }
}

Phong::Phong(const Phong &m) : Material(m)
{
    if (m.ambient_brdf)
    {
        ambient_brdf = m.ambient_brdf;
    }
    else
    {
        ambient_brdf = new Lambertian;
    }

    if (m.diffuse_brdf)
    {
        diffuse_brdf = m.diffuse_brdf;
    }
    else
    {
        diffuse_brdf = new Lambertian;
    }

    if (m.specular_brdf)
    {
        specular_brdf = m.specular_brdf;
    }
    else
    {
        specular_brdf = new GlossySpecular;
    }
}

// operator overloading

Phong &Phong::operator=(const Phong &phong)
{
    Material::operator=(phong);
    if (ambient_brdf && phong.ambient_brdf)
    {
        delete ambient_brdf;
        ambient_brdf = phong.ambient_brdf;
    }
    if (diffuse_brdf && phong.diffuse_brdf)
    {
        delete diffuse_brdf;
        diffuse_brdf = phong.diffuse_brdf;
    }
    if (specular_brdf && phong.specular_brdf)
    {
        delete specular_brdf;
        specular_brdf = phong.specular_brdf;
    }
    return (*this);
}

// setters and getters

void Phong::set_ka(const float k)
{
    ambient_brdf->set_kd(k);
}

void Phong::set_kd(const float k)
{
    diffuse_brdf->set_kd(k);
}

void Phong::set_ks(const float k)
{
    specular_brdf->set_ks(k);
}

void Phong::set_cd(const RGBColor &c)
{
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
    specular_brdf->set_cs(c);
}

void Phong::set_exp(const float exp_)
{
    specular_brdf->set_exp(exp_);
}

// color logic

RGBColor Phong::shade(const ShadeInfo &sinfo) const
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
                L += (diffuse_brdf->f(sinfo, wo, wi) +
                      specular_brdf->f(sinfo, wo, wi)) *
                     sinfo.w->lights[j]->L(sinfo) * ndotwi;
            }
        }
    }

    return (L);
}
