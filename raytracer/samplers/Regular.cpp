#include <iostream>
#include <math.h>
#include "Regular.hpp"
#include "../cameras/Camera.hpp"
#include "../utilities/Ray.hpp"
#include "../world/ViewPlane.hpp"


Regular::Regular(Camera* c_ptr, ViewPlane* v_ptr): Sampler(c_ptr, v_ptr) 
{
    generate_samples();
}

Regular::Regular(const Regular& camera): Sampler(camera) {}

Regular& Regular::operator=(const Regular& other)
{
    this->camera_ptr = other.camera_ptr;
    this->viewplane_ptr = other.viewplane_ptr;
    return *this;
}

void Regular::generate_samples(){
    this->num_sets = 50;
	int n = (int) sqrt(this->viewplane_ptr->num_samples);
	for (int j = 0; j < num_sets; j++)
		for (int p = 0; p < n; p++)		
			for (int q = 0; q < n; q++)
				samples.push_back(Point3D((q + 0.5) / n, (p + 0.5) / n, 0));
}

std::vector<Ray> Regular::get_rays(int px, int py) const
{
    int n = (int)std::sqrt((float)this->viewplane_ptr->num_samples);
    std::vector<Ray> rays;

    double hres = this->viewplane_ptr->get_hres();
    double vres = this->viewplane_ptr->get_vres();

    ViewPlane* vp = this->viewplane_ptr;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Vector3D vp_res = vp->bottom_right - vp->top_left;
            double x_frac = (double)px/ hres;
            double y_frac = (double)py/ vres;
            Point3D pp(vp->top_left + Vector3D(x_frac * vp_res.x + (j + 0.5)/n, y_frac * vp_res.y + (i + 0.5)/n, 0));
            pp = pp * vp->s;
            Ray r(pp, camera_ptr->get_direction(pp));
            r.d.normalize();
            rays.push_back(r);
        }
    }
    return rays;
}

inline int rand_int(){
	return (int) rand();
}

Point3D Regular::sample_unit_square(){

    num_sets = 50;
    count = 0;
    jump = 0;


    if(count % this->viewplane_ptr->num_samples == 0){
        jump = (rand_int() % num_sets) * this->viewplane_ptr->num_samples;
    }
    return (samples[jump + (count++)%this->viewplane_ptr->num_samples]);
}
