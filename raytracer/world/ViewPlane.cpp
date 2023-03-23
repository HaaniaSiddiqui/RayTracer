#include <iostream>
#include "ViewPlane.hpp"

ViewPlane::ViewPlane()
{
    vres, hres = 480, 640;    
    top_left = Point3D(-320, 240, 0);
    bottom_right = Point3D(320, -240, 0);

    Vector3D v1 = top_left - Point3D(320, 240, 0);
    Vector3D v2 = bottom_right - Point3D(320, 240, 0);
    v1.normalize();
    v2.normalize();
    normal = v1 ^ v2;
}

int ViewPlane::get_hres() const
{
    return hres;
}

void ViewPlane::set_hres(int h)
{
    this->hres = h;
}

int ViewPlane::get_vres() const
{
    return vres;
}

void ViewPlane::set_vres(int v)
{
    this->vres = v;
}

void ViewPlane::set_max_depth(const int d) {
	this->max_depth = d;
}