#pragma once

#include "Light.hpp"
#include "../Materials/Material.hpp"
#include "../geometry/Geometry.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"

class AreaLight : public Light
{
private:
    Geometry *object_ptr;
    Material *material_ptr;
    Point3D sample_point;
    Vector3D light_normal;
    Vector3D wi;

public:
    // constructors
    AreaLight();
    AreaLight(const AreaLight &light);

    // destructor
    ~AreaLight() = default;

    // operator overloader
    AreaLight &operator=(const AreaLight &light);

    // setter getters
    void set_object(Geometry *object);

    // get direction
    virtual Vector3D get_direction(const ShadeInfo &sinfo);

    // check if in shadow
    virtual bool in_shadow(const Ray &ray, const ShadeInfo &sinfo) const;
    virtual RGBColor L(const ShadeInfo &sinfo) const;

    virtual float G(const ShadeInfo &sinfo) const;
    virtual float pdf(const ShadeInfo &sinfo) const;
};
