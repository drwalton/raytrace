#ifndef RAYTRACE_SCENE_HPP_INCLUDED
#define RAYTRACE_SCENE_HPP_INCLUDED

#include "CollisionInfo.hpp"
#include "Ray.hpp"
#include "PointLight.hpp"
#include "PhotonMap.hpp"

#include <vector>
#include <memory>

class Object;

class Scene final {
public:
	Scene();
	~Scene() throw();
	
	//Trace a ray and return a color.
	glue::vec3 trace(const Ray &ray) const;

	//Test for collision, return information about it.
	CollisionInfo collide(const Ray &ray) const;

	void tracePhoton(const Photon &p, PhotonMap *map);

	//Trace photon, and possibly add to caustic map.
	void traceGlobalPhoton(const Photon &p);

	//Trace photon, and possibly add to caustic map.
	void traceCausticPhoton(const Photon &p);

	std::vector<std::unique_ptr<Object>> objectList;

	std::vector<PointLight> pointLightList;

	glue::vec3 globalLightLevel;

	glue::vec3 defaultColor;

	PhotonMap globalPhotonMap, causticPhotonMap;
};

#endif
