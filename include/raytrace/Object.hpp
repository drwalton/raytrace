#ifndef RAYTRACE_OBJECT_HPP_INCLUDED
#define RAYTRACE_OBJECT_HPP_INCLUDED

#include "Ray.hpp"
#include "Photon.hpp"
#include "PhotonMap.hpp"
#include "CollisionInfo.hpp"

class Scene;

class Object {
public:
	explicit Object();
	virtual ~Object() throw();

	///\brief Check for collision with the supplied ray, and return data if a
	///       collision occurs.
	///\note Implementations should check the object's properties and the ray's
	///      collision mask, and exit early (returning no collision) if they are
	///      not compatible.
	virtual CollisionInfo collide(const Ray &ray) const = 0;

	///\brief The material shader takes as input the incoming ray,
	///       the collision info and the scene.
	std::function<glue::vec3(
		const Ray &ray, const CollisionInfo &info, const Scene &scene)> materialShader;

	///\brief The photon shader describes how the material behaves in the global photon
	///       mapping phase.
	std::function<void(const Photon &photon, const CollisionInfo &info, Scene &scene, PhotonMap *map)> photonShaderGlobal;

	///\brief The photon shader describes how the material behaves in the caustic photon
	///       mapping phase.
	std::function<void(const Photon &photon, const CollisionInfo &info, Scene &scene, PhotonMap *map)> photonShaderCaustic;

	///\brief Base colour of the object. Used by some shaders.
	glue::vec3 color;

	///\brief Collision mask indicating which ray collisions it should be involved
	///       in.
	CollisionMask properties;
};

#endif
