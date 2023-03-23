#pragma once

#include "Sampler.hpp"

class Random : public Sampler {
protected:
  // add members to cache values to avoid recomputation in get_rays().

public:
  // Constructors.
  Random() = default;                      // initializes members to NULL.
  Random(Camera *c_ptr, ViewPlane *v_ptr); // set members.

  // Copy constuctor and assignment operator.
  Random(const Random &camera);
  Random &operator=(const Random &other);

  // Desctructor.
  virtual ~Random() = default;

  // Shoot a ray of weight 1 through the center of the pixel.
  std::vector<Ray> get_rays(int px, int py) const override;
};
