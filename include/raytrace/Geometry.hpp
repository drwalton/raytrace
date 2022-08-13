#ifndef RAYTRACE_GEOMETRY_HPP_INCLUDED
#define RAYTRACE_GEOMETRY_HPP_INCLUDED

#include "glue/VectorTypes.hpp"

//Need to move rays slightly out of intersection points when casting subsequent rays.
//This delta sets the distance the new ray origin is moved away from the surface.
const float SURFACE_DELTA = 0.05f;

glue::vec3 refract(const glue::vec3 &I, const glue::vec3 &N, const float &ior);

float fresnelReflectance(const glue::vec3 &I, const glue::vec3 &N, const float &ior);

#endif
