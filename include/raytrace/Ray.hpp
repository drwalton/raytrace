#ifndef RAYTRACE_RAY_HPP_INCLUDED
#define RAYTRACE_RAY_HPP_INCLUDED

#include <glue/VectorTypes.hpp>
#include "CollisionMask.hpp"

struct Ray {
	Ray() :depth(0), mask(ALL) {}
	glue::vec3 dir;
	glue::vec3 origin;
	unsigned char depth;

	CollisionMask mask;
};

#endif
