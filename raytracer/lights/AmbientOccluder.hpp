#pragma once

#include "Ambient.hpp"
#include "../Samplers/Sampler.hpp"

class AmbientOccluder : public Ambient
{
private:
    Vector3D u, v, w;
    Sampler *sampler_ptr;
    RGBColor min_amount;

public:
    // constructor
    AmbientOccluder();
    AmbientOccluder(const AmbientOccluder &ambient);

    //operator overloading
    AmbientOccluder &operator=(const AmbientOccluder &ambient);

    // setter getters
    void set_sampler(Sampler *s_ptr);

    virtual Vector3D get_direction(ShadeInfo &sinfo);

    // check if in shadow
    virtual bool in_shadow(const Ray &ray, const ShadeInfo &sinfo) const;
    virtual RGBColor L(ShadeInfo &sinfo);
};
