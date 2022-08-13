#ifndef RAYTRACE_SPHERE_HPP_INCLUDED
#define RAYTRACE_SPHERE_HPP_INCLUDED

#include "Object.hpp"

class Sphere : public Object {
public:
	Sphere(const glue::vec3 &center, float radius);
	virtual ~Sphere() throw();

	virtual CollisionInfo collide(const Ray &ray) const;
private:
	glue::vec3 center_;
	float radius_, radius2_;
};

#endif
