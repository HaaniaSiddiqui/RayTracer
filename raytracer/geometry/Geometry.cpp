
#include <iostream>
#include "Geometry.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"

// Constructors.
Geometry::Geometry() : material_ptr(nullptr) {}

// Get/set material.
Material *Geometry::get_material() const
{
    return material_ptr;
}

void Geometry::set_material(Material *mPtr)
{
    this->material_ptr = mPtr;
}

void Geometry::add_object(Geometry *object_ptr) {}

Vector3D Geometry::get_normal(const Point3D &p) const
{
    return Vector3D();
}

Point3D Geometry::sample()
{
    return Point3D();
}

float Geometry::pdf(const ShadeInfo &sinfo)
{
    return 1.0;
}
