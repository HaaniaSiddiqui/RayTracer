#pragma once

#include "Sampler.hpp"

class Regular : public Sampler {
protected:
  // add members to cache values to avoid recomputation in get_rays().

public:
  // Constructors.
  Regular() = default;                      // initializes members to NULL.
  Regular(Camera *c_ptr, ViewPlane *v_ptr); // set members.

  // Copy constuctor and assignment operator.
  Regular(const Regular &camera);
  Regular &operator=(const Regular &other);

  virtual Point3D sample_unit_square();

  void generate_samples();

  // Desctructor.
  virtual ~Regular() = default;

  // Shoot a ray of weight 1 through the center of the pixel.
  std::vector<Ray> get_rays(int px, int py) const override;
};
