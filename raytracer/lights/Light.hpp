#pragma once

//Credits - Kevin Suffern

#include "../utilities/RGBColor.hpp"

class Vector3D;
class ShadeInfo;
class Ray;

class Light
{
protected:
    RGBColor color;
    float ls;
    bool shadows;

public:
    // constructor

    Light(const bool shadows_ = false);
    Light(const Light &light);

    //operator overloading
    Light &operator=(const Light &rhs);

    // destructor
    virtual ~Light() = default;

    // methods
    bool casts_shadows() const;
    void set_shadows(const bool shadows_);
    void set_color(const RGBColor &c);

    virtual Vector3D get_direction(const ShadeInfo &sinfo) = 0;
    virtual RGBColor L(const ShadeInfo &sinfo) const = 0;
    virtual float G(const ShadeInfo &sinfo) const;
    virtual float pdf(const ShadeInfo &sinfo) const;

    virtual bool in_shadow(const Ray &ray, const ShadeInfo &sr) const = 0;
};
