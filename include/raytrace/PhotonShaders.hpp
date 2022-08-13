#ifndef RAYTRACE_PHOTONSHADERS_HPP_INCLUDED
#define RAYTRACE_PHOTONSHADERS_HPP_INCLUDED

#include "Photon.hpp"
#include "CollisionInfo.hpp"
#include "Scene.hpp"

void absorbPhotonShader
	(const Photon &photon, const CollisionInfo &info, 
	Scene &scene, PhotonMap *map);

void diffusePhotonShader
	(const Photon &photon, const CollisionInfo &info, 
	Scene &scene, PhotonMap *map);

void perfectRefractPhotonShader
	(const Photon &photon, const CollisionInfo &info, 
	Scene &scene, PhotonMap *map);

#endif
