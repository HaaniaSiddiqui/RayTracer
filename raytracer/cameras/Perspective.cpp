#include <iostream>
#include "../utilities/Vector3D.hpp"
#include "Perspective.hpp"

// constructors
Perspective::Perspective() : pos(0) {}
Perspective::Perspective(float c) : pos(c) {}
Perspective::Perspective(float x, float y, float z) : pos(x, y, z) {}
Perspective::Perspective(const Point3D &pt) : pos(pt.x, pt.y, pt.z) {}
Perspective::Perspective(const Perspective &camera) : pos(camera.pos) {}

// operator overloading
Perspective &Perspective::operator=(const Perspective &other)
{
    this->pos = other.pos;
    return *this;
}

// Get direction of projection for a point.
Vector3D Perspective::get_direction(const Point3D &p) const
{
    Vector3D dir = p - pos;
    dir.normalize();
    return dir;
}
