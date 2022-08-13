#ifndef RAYTRACE_COLLISIONINFO_HPP_INCLUDED
#define RAYTRACE_COLLISIONINFO_HPP_INCLUDED

#include "glue/VectorTypes.hpp"

class Object;

struct CollisionInfo {
	bool collisionOccurred;

	glue::vec3 collisionPoint;
	glue::vec3 collisionNormal;
	float squaredDistance;

	const Object *collidedObject;
};

#endif
