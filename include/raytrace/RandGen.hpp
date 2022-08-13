#ifndef RAYTRACE_RANDGEN_HPP_INCLUDED
#define RAYTRACE_RANDGEN_HPP_INCLUDED

#include "glue/VectorTypes.hpp"
#include <random>

template<typename URNG>
glue::vec3 uniformRandSphere(URNG &generator)
{
	std::uniform_real_distribution<float> dist(-1.f, 1.f);
	glue::vec3 vec;
	do {
		vec.x() = dist(generator);
		vec.y() = dist(generator);
		vec.z() = dist(generator);
	} while (vec.squaredNorm() > 1.f);
	return vec.normalized();
}

template<typename URNG>
glue::vec3 uniformRandHemisphere(URNG &generator, const glue::vec3 &norm)
{
	glue::vec3 vec;
	do {
		vec = uniformRandSphere(generator);
	} while (vec.dot(norm) < 0.f);
	return vec;
}

#endif
