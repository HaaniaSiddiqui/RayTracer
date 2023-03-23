#include <iostream>
#include <math.h>
#include "World.hpp"
#include "../utilities/Constants.hpp"
#include "../cameras/Camera.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../geometry/Geometry.hpp"
#include "../materials/Material.hpp"
#include "../lights/Ambient.hpp"
#include "../samplers/Sampler.hpp"
#include "../utilities/Image.hpp"
#include "../tracer/Tracer.hpp"
#include "../happly/happly.h"
#include "../geometry/Triangle.hpp"

using namespace std;

World::World(): bg_color(0), camera_ptr(NULL), sampler_ptr(NULL), ambient_ptr(new Ambient) {}

World::~World()
{
    this->geometry.clear();
    this->camera_ptr = NULL;
    this->sampler_ptr = NULL;
    this->tracer_ptr = NULL;
}

void World::add_geometry(Geometry* geom_ptr)
{
    this->geometry.push_back(geom_ptr);
}

void World::add_light(Light* light_ptr)
{
    this->lights.push_back(light_ptr);
}

void World::set_tracer(Tracer* t_ptr)
{
    this->tracer_ptr = t_ptr;
}

void World::set_ambient(Ambient* ambient_ptr_)
{
    this->ambient_ptr = ambient_ptr_;
}

void World::set_camera(Camera* c_ptr)
{
    this->camera_ptr = c_ptr;
}

RGBColor World::max_to_one(const RGBColor& c) const  {
	float max_value = std::max(c.r, std::max(c.g, c.b));
	
	if (max_value > 1.0){
		return (c / max_value);
	}
	else
		return (c);
}

RGBColor World::clamp_to_color(const RGBColor& raw_color) const {
	RGBColor c(raw_color);
	
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0; c.g = 0.0; c.b = 0.0;
	}
		
	return (c);
}

ShadeInfo World::hit_objects(const Ray& ray)
{
    // Reference: The book Raytracing from the ground up

    ShadeInfo sr(*this);

    double t;
    double tmin = kHugeValue;
    Point3D hitt;
    Vector3D norm;

    int num_objects = geometry.size();

    for (int i = 0; i < num_objects; i++)
    {
        if(geometry[i]->hit(ray, t, sr) && (t < tmin)){
            sr.hit = true;
            tmin = t;
            sr.material_ptr = geometry[i]->get_material();
            norm = sr.normal;
            hitt = sr.hit_point;
        }
    }

    if(sr.hit){
        sr.t = tmin;
        sr.hit_point = hitt;
        sr.normal = norm;
    }

    return sr;
}

void World::render_scene(){
    Sampler *sampler = this->sampler_ptr;
    ViewPlane &viewplane = this->vplane;
    Tracer* tracer = this->tracer_ptr;
    Image image(viewplane);

    int n = (int)std::sqrt((float)vplane.num_samples);

    std::vector<Ray> rays;
    for (int x = 0; x < viewplane.hres; x++) {   // across.
        for (int y = 0; y < viewplane.vres; y++) { // down.
        // Get rays for the pixel from the sampler. The pixel color is the
        // weighted sum of the shades for each ray.
        RGBColor pixel_color(0);
        rays = sampler->get_rays(x, y);
        for (const auto &ray : rays) {
            if(viewplane.max_depth != 0){
                pixel_color += tracer->trace_ray(ray, 0);
            }
            else{
                pixel_color += tracer->trace_ray(ray);
            }   
        }

        pixel_color /= vplane.num_samples;
        // Save color to image.
        image.set_pixel(x, y, pixel_color);
        // std::cout << pixel_color << "\n";
        }
    }
    // Write image to file.
    image.write_ppm("sample.ppm");

    std::cout << "Wrote image.\n";    
}


void World::add_mesh(std::string file_name, Material* mat_ptr, Point3D bottom, Point3D top, Grid* grid_ptr) {

    happly::PLYData plyIn(file_name);
    //extracting vertices
    std::vector<array<double, 3>> vertices = plyIn.getVertexPositions(); 
    //extracting faces
    std::vector<vector<size_t>> faces = plyIn.getFaceIndices<size_t>();
    //array of points on screen
    std::vector<Point3D> point_arr;
    //minimum 
    Point3D modelMin(vertices[0][0], vertices[0][1], vertices[0][2]);
    //maximum
    Point3D modelMax(vertices[0][0], vertices[0][1], vertices[0][2]);
    //populating array of points
    for (const auto& v : vertices) {
        Point3D object(v[0], v[1], v[2]);
        point_arr.push_back(object);
        modelMin = min(modelMin, object);
        modelMax = max(modelMax, object);
    }
    for (auto& p: point_arr) {
        p = Point3D::interpolate(modelMin, modelMax, p, bottom, top);
    }
    //creating mesh of triangles
    for (const auto& f : faces) {
      Triangle* triangleMesh = new Triangle(point_arr[f[0]], point_arr[f[1]], point_arr[f[2]]);
      triangleMesh->set_material(mat_ptr);
      grid_ptr->add_object(triangleMesh);
    }
    
}