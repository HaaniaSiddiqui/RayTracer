#include <iostream>
#include <math.h>
#include "Random.hpp"
#include "../cameras/Camera.hpp"
#include "../utilities/Ray.hpp"
#include "../world/ViewPlane.hpp"


Random::Random(Camera* c_ptr, ViewPlane* v_ptr): Sampler(c_ptr, v_ptr) {}
Random::Random(const Random& camera): Sampler(camera) {}

Random& Random::operator=(const Random& other)
{
    this->camera_ptr = other.camera_ptr;
    this->viewplane_ptr = other.viewplane_ptr;
    return (*this);
}

inline float
rand_float(void){
    return ((float) rand()) / (float)RAND_MAX;
}

std::vector<Ray> Random::get_rays(int px, int py) const
{
    int n = (int)std::sqrt((float)this->viewplane_ptr->num_samples);
    std::vector<Ray> rays;

    double hres = this->viewplane_ptr->get_hres();
    double vres = this->viewplane_ptr->get_vres();

    ViewPlane* vp = this->viewplane_ptr;

    for (int i = 0; i < n; i++) {
        Vector3D vp_res = vp->bottom_right - vp->top_left;
        double x_frac = (double)px/ hres;
        double y_frac = (double)py/ vres;
        Point3D pp(viewplane_ptr->top_left + Vector3D(x_frac * vp_res.x + rand_float(), 
                                                        y_frac * vp_res.y + rand_float(), 0));
        Ray r(pp, camera_ptr->get_direction(pp));
        r.d.normalize();
        rays.push_back(r);
    }
    return rays;
}
