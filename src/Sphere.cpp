#include "raytrace/Sphere.hpp"
#include "raytrace/Polynomial.hpp"

using namespace glue;

Sphere::Sphere(const glue::vec3 &center, float radius)
	:center_(center), radius_(radius), radius2_(radius*radius)
{}

Sphere::~Sphere() throw()
{}

CollisionInfo Sphere::collide(const Ray &ray) const
{
	CollisionInfo info;
	info.collisionOccurred = false;
	if((properties & ray.mask) == 0) {
		return info;
	}

	vec3 L = ray.origin - center_;
	float a = ray.dir.dot(ray.dir);
	float b = 2 * ray.dir.dot(L);
	float c = L.dot(L) - radius2_;

	float t0, t1; //Two intersection points

	if (!solveQuadratic(a, b, c, t0, t1)) {
		return info;	//Early return: no roots.
	}

	if (t0 > t1) std::swap(t0, t1);

	if (t0 < 0) {
		t0 = t1; // if t0 is negative, let's use t1 instead
		if (t0 < 0) {
			return info; // Early return: intersections behind origin on ray.
		}
	}

	float t = t0; //Closest intersection point - it's valid!

	//Populate collision information.
	info.collisionOccurred = true;
	info.collisionPoint = ray.origin + t*ray.dir;
	info.squaredDistance = t*t * ray.dir.dot(ray.dir);
	info.collisionNormal = (info.collisionPoint - center_).normalized();
	info.collidedObject = this;

	return info;
}
