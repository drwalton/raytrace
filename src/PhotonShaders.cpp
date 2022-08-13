#include "raytrace/PhotonShaders.hpp"
#include "raytrace/Geometry.hpp"
#include "raytrace/RandGen.hpp"

const float IOR = 1.5f;

void absorbPhotonShader
	(const Photon &photon, const CollisionInfo &info, 
	Scene &scene, PhotonMap *map)
{
	Photon absorbedPhoton = photon;
	//TODO change this to reflect lambertian cosine distribution
	std::default_random_engine eng;
	absorbedPhoton.ray.dir = uniformRandHemisphere(eng, info.collisionNormal);	
	absorbedPhoton.ray.origin = info.collisionPoint;	
	++absorbedPhoton.ray.depth;
	map->addPhoton(absorbedPhoton);
}

void diffusePhotonShader
	(const Photon &photon, const CollisionInfo &info, 
	Scene &scene, PhotonMap *map)
{
	Photon absorbedPhoton = photon;
	absorbedPhoton.ray.dir = -photon.ray.dir;	
	absorbedPhoton.ray.origin = info.collisionPoint;	
	++absorbedPhoton.ray.depth;
	map->addPhoton(absorbedPhoton);
}

void perfectRefractPhotonShader
	(const Photon &photon, const CollisionInfo &info,
	Scene &scene, PhotonMap *map)
{
	Photon refractedPhoton = photon;
	refractedPhoton.ray.mask = ALL;

	refractedPhoton.ray.dir = refract(refractedPhoton.ray.dir, info.collisionNormal, IOR);
	refractedPhoton.ray.origin = info.collisionPoint + SURFACE_DELTA * refractedPhoton.ray.dir;
	++refractedPhoton.ray.depth;
	scene.tracePhoton(refractedPhoton, map);
}
