#include "Sampler.hpp"
#include <iostream>
#include "../cameras/Camera.hpp"
#include "../world/ViewPlane.hpp"

Sampler::Sampler(): camera_ptr(NULL), viewplane_ptr(NULL) {}
Sampler::Sampler(Camera* c_ptr, ViewPlane* v_ptr): camera_ptr(c_ptr), viewplane_ptr(v_ptr) {}

Point3D Sampler::sample_unit_square(){
    return Point3D(0.0);
}