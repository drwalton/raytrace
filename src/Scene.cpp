#include "raytrace/Scene.hpp"

#include "raytrace/Object.hpp"

#include <cfloat>

const unsigned char MAX_RAY_DEPTH = 10;

using namespace glue;

Scene::Scene()
	:globalLightLevel(0.1f, 0.1f, 0.1f),
	defaultColor(0.2f, 0.2f, 0.2f)
{}

Scene::~Scene() throw()
{}

vec3 Scene::trace(const Ray &ray) const
{
	if (ray.depth > MAX_RAY_DEPTH) {
		return defaultColor;
	}

	CollisionInfo info = collide(ray);

	if (info.collisionOccurred) {
		//Execute object's shader
		return info.collidedObject->materialShader(ray, info, *this);
	}

	return defaultColor;
}

void Scene::tracePhoton(const Photon &p, PhotonMap *map)
{
	if (p.ray.depth > MAX_RAY_DEPTH) {
		return;
	}

	CollisionInfo info = collide(p.ray);

	if (info.collisionOccurred) {
		if (map == &(this->causticPhotonMap)) {
			info.collidedObject->photonShaderCaustic(p, info, *this, map);
		}
		else {
			info.collidedObject->photonShaderGlobal(p, info, *this, map);
		}
	}

}

void Scene::traceCausticPhoton(const Photon &photon)
{
	Photon causticPhoton = photon;
	causticPhoton.ray.mask = CAUSTIC_BIT;
	tracePhoton(causticPhoton, &causticPhotonMap);
}

void Scene::traceGlobalPhoton(const Photon &photon)
{
	tracePhoton(photon, &globalPhotonMap);
}

CollisionInfo Scene::collide(const Ray &ray) const
{
	CollisionInfo ans;
	ans.collisionOccurred = false;
	ans.squaredDistance = FLT_MAX;

	for(const std::unique_ptr<Object> &o : objectList) {
		CollisionInfo i = o->collide(ray);
		if(i.collisionOccurred && i.squaredDistance < ans.squaredDistance) {
			ans = i;
		}
	}

	return ans;
}
