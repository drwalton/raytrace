#include "raytrace/Object.hpp"

#include "raytrace/Shaders.hpp"

using namespace glue;


Object::Object()
	:materialShader(defaultShader), color(1.f, 1.f, 1.f),
	properties(CollisionMask(DIFFUSE_BIT | CASTS_SHADOWS_BIT))
{}

Object::~Object() throw()
{}
