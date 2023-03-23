#include <iostream>

#include "materials/Cosine.hpp"

#include "samplers/Sampler.hpp"

#include "utilities/Image.hpp"
#include "utilities/RGBColor.hpp"
#include "utilities/Ray.hpp"
#include "utilities/ShadeInfo.hpp"

#include "world/World.hpp"
#include "world/ViewPlane.hpp"

int main(int argc, char **argv)
{
  World world;

  // build world
  world.build();

  // render scene completely
  world.render_scene();

  return 0;
}
