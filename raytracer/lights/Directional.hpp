#pragma once

#include "Light.hpp"
#include "../Utilities/Vector3D.hpp"
#include "../Utilities/RGBColor.hpp"

#include "../World/World.hpp"
#include "../Utilities/ShadeInfo.hpp"

class Directional : public Light
{
private:
    float ls;
    RGBColor color;
    Vector3D dir; // direction the light comes from

public:
    // constructors, operator overloading, and destructor
    Directional();
    Directional(const Directional &dl);
    Directional &operator=(const Directional &rhs);
    virtual ~Directional() = default;

    void set_ls(const float b);

    // setter getters
    void set_color(const float c);
    void set_color(const RGBColor &c);
    void set_color(const float r, const float g, const float b);

    void set_direction(Vector3D d);
    void set_direction(float dx, float dy, float dz);

    // get direction
    virtual Vector3D get_direction(const ShadeInfo &sr) override;
    virtual RGBColor L(const ShadeInfo &sr) const;

    // check if in shadow
    virtual bool in_shadow(const Ray &ray, const ShadeInfo &sr) const;
};
