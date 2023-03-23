#include "Material.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/Constants.hpp"

// Get color functions
RGBColor Material::area_light_shade(ShadeInfo &sinfo)
{
    return black;
}

RGBColor Material::path_shade(ShadeInfo &sinfo)
{
    return black;
}

RGBColor Material::get_Le(const ShadeInfo &sinfo) const
{
    return black;
}
