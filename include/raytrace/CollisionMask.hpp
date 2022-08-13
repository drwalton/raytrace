#ifndef RAYTRACE_COLLISIONMASK_HPP_INCLUDED
#define RAYTRACE_COLLISIONMASK_HPP_INCLUDED

///\brief A CollisionMask is a bitmask used to control which categories of
///       Object a Ray will collide with.
///\note A Ray will only collide with an Object if the ray's if
///      ray.mask & object.properties != 0
enum CollisionMask : unsigned char {

	//The object is always ignored when raycasting.
	NONE = 0,

	//Indicates that an object is diffuse.
	DIFFUSE_BIT = 1,

	//Indicates that an object should be involved in the caustic photon map.
	CAUSTIC_BIT = 1 << 1,

	//Indicates that the object should be involved in shadow ray calculations.
	CASTS_SHADOWS_BIT = 1 << 2,

	//The object always collides with rays.
	ALL = 0xff
};

#endif
