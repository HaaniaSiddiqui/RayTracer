#pragma once

/**
   This file declares the Geometry class which is an abstract class from which
   other concrete geometric objects will inherit.

   Courtesy Kevin Suffern.
*/

#include <string>

class BBox;
class Material;
class Ray;
class ShadeInfo;
class Point3D;
class Vector3D;

class Geometry
{
protected:
  mutable Material *material_ptr; // this object's material.

public:
  // Constructors.
  Geometry(); // sets material_ptr to NULL.

  // Copy constructor and assignment operator.
  Geometry(const Geometry &object) = default;
  Geometry &operator=(const Geometry &rhs) = default;

  // Destructor.
  virtual ~Geometry() = default;

  // String representation.
  virtual std::string to_string() const = 0;

  // Get/set material.
  Material *get_material() const;
  void set_material(Material *mPtr);

  // Ray intersection. Set t and sinfo as per intersection with this object.
  virtual bool hit(const Ray &ray, double &t, ShadeInfo &sinfo) const = 0;
  virtual bool shadow_hit(const Ray &ray, float &t) const = 0;

  virtual Vector3D get_normal(const Point3D &p) const;
  virtual Point3D sample();
  virtual float pdf(const ShadeInfo &sinfo);

  virtual void // required for compound objects
  add_object(Geometry *object_ptr);

  // Get bounding box.
  virtual BBox getBBox() const = 0;
};
