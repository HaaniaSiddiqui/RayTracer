#include <iostream>
#include "Simple.hpp"
#include "../cameras/Camera.hpp"
#include "../utilities/Ray.hpp"
#include "../world/ViewPlane.hpp"


Simple::Simple(Camera* c_ptr, ViewPlane* v_ptr): Sampler(c_ptr, v_ptr) {}
Simple::Simple(const Simple& camera): Sampler(camera) {}

Simple& Simple::operator=(const Simple& other)
{
    this->camera_ptr = other.camera_ptr;
    this->viewplane_ptr = other.viewplane_ptr;
    return *this;
}

std::vector<Ray> Simple::get_rays(int px, int py) const
{
    std::vector<Ray> rays;
    Point3D sample_p; 
    Ray ray;
    Vector3D vp_res = this->viewplane_ptr->bottom_right - this->viewplane_ptr->top_left;

    double hres = this->viewplane_ptr->get_hres();
    double vres = this->viewplane_ptr->get_vres();

    double x_frac = (double)px / hres;
    double y_frac = (double)py / vres;

    Vector3D offset(x_frac * vp_res.x, y_frac * vp_res.y, 0);
    sample_p = this->viewplane_ptr->top_left + offset;

    ray.o = sample_p;
    ray.d = this->camera_ptr->get_direction(ray.o);
    ray.d.normalize();
    rays.push_back(ray);

    return rays;
}

inline int rand_int(){
	return (int) rand();
}

Point3D Simple::sample_unit_square(){

    num_sets = 50;
    count = 0;
    jump = 0;


    if(count % this->viewplane_ptr->num_samples == 0){
        jump = (rand_int() % num_sets) * this->viewplane_ptr->num_samples;
    }
    return (samples[jump + (count++)%this->viewplane_ptr->num_samples]);
}
