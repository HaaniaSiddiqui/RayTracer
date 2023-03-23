#pragma once

/**
   This file declares the World class which contains all the information about
   the scene - geometry and materials, lights, viewplane, camera, samplers, and
   acceleration structures.

   It also traces rays through the scene.

   Courtesy Kevin Suffern.
*/

#include <vector>

#include "../utilities/RGBColor.hpp"
#include "../geometry/Grid.hpp"

#include "ViewPlane.hpp"

class Camera;
class Geometry;
class Ray;
class Sampler;
class ShadeInfo;
class Light;
class Tracer;
class Ambient;

class World {
public:
  ViewPlane vplane;
  RGBColor bg_color;
  std::vector<Geometry *> geometry;
  Tracer* tracer_ptr;
  Light* ambient_ptr;
  Camera *camera_ptr;
  Sampler *sampler_ptr;
  std::vector<Light *> lights;

public:
  // Constructors.
  World(); // initialize members.

  // Destructor.
  ~World(); // free memory.

  // Add to the scene.
  void add_geometry(Geometry *geom_ptr);
  void add_light(Light *light_ptr);
  void set_ambient(Ambient* amb_ptr);
  void set_camera(Camera *c_ptr);
  void set_tracer(Tracer* t_ptr);

  RGBColor max_to_one(const RGBColor& c) const;
  RGBColor clamp_to_color(const RGBColor& c) const;

  // Build scene - add all geometry, materials, lights, viewplane, camera,
  // samplers, and acceleration structures
  void build();

  void render_scene();

  // Returns appropriate shading information corresponding to intersection of
  // the ray with the scene geometry.
  ShadeInfo hit_objects(const Ray &ray);
  void add_mesh(std::string file_name, Material* mat_ptr, Point3D bottom, Point3D top, Grid* grid_ptr);
};
