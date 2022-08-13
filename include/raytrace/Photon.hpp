#ifndef RAYTRACE_PHOTON_HPP_INCLUDED
#define RAYTRACE_PHOTON_HPP_INCLUDED

#include "Ray.hpp"

struct Photon
{
	Ray ray;
	glue::vec3 power;
};

#endif
