#include "raytrace/Plane.hpp"
#include <cfloat>

Plane::Plane(const glue::vec3 &normal, float d)
	:normal_(normal), d_(d)
{}

Plane::~Plane() throw()
{}

CollisionInfo Plane::collide(const Ray &ray) const
{
	CollisionInfo info;
	info.collisionOccurred = false;
	if((properties & ray.mask) == 0) {
		return info;
	}

	float rayDotN = ray.dir.dot(normal_);
	if (fabsf(rayDotN) < FLT_EPSILON) {
		//Ray parallel to plane
		return info;
	}

	float t = -(ray.origin.dot(normal_) + d_) / rayDotN;
	if (t <= 0.f) {
		//Collision behind or at origin of ray.
		return info;
	}

	info.collisionOccurred = true;
	info.collisionNormal = normal_;
	info.collisionPoint = ray.origin + t*ray.dir;
	info.squaredDistance = t*t*ray.dir.dot(ray.dir);
	info.collidedObject = this;

	return info;
}
