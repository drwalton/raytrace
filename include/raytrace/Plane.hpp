#ifndef RAYTRACE_PLANE_HPP_INCLUDED
#define RAYTRACE_PLANE_HPP_INCLUDED

#include "Object.hpp"

///\brief A plane is a simple plane of infinite extent, described by a normal
///       direction and distance from the origin.
class Plane : public Object {
public:
	Plane(const glue::vec3 &normal, float d);
	virtual ~Plane() throw();

	virtual CollisionInfo collide(const Ray &ray) const;

private:
	glue::vec3 normal_;
	float d_;
};

#endif
