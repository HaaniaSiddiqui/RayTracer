#pragma once

#include "Light.hpp"
#include "../utilities/Vector3D.hpp"

class Ambient : public Light
{
protected:
    float ls;
    RGBColor color;

public:
    // constructor
    Ambient();
    Ambient(const Ambient &a);

    //operator overloading
    Ambient &operator=(const Ambient &rhs);

    // destructor
    virtual ~Ambient() = default;

    // setter getters
    void set_color(const float c);
    void set_color(const RGBColor &c);
    void set_color(const float r, const float g, const float b);
    void set_ls(const float b);

    virtual Vector3D get_direction(const ShadeInfo &s);
    virtual RGBColor L(const ShadeInfo &s) const;

    // check if in shadow
    virtual bool in_shadow(const Ray &ray, const ShadeInfo &sr) const;
};
