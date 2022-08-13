#ifndef RAYTRACE_POINTLIGHT_HPP_INCLUDED
#define RAYTRACE_POINTLIGHT_HPP_INCLUDED

#include "glue/VectorTypes.hpp"

struct PointLight
{
	PointLight(const glue::vec3 &pos, const glue::vec3 &power);
	glue::vec3 pos;
	glue::vec3 power;
};

#endif
