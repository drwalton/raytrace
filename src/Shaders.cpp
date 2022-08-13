#define _USE_MATH_DEFINES
#include <cmath>
#include "raytrace/Shaders.hpp"
#include "raytrace/Ray.hpp"
#include "raytrace/CollisionInfo.hpp"
#include "raytrace/Scene.hpp"
#include "raytrace/Object.hpp"
#include "raytrace/Geometry.hpp"

using namespace glue;


vec3 defaultShader(const Ray &ray, const CollisionInfo &info, const Scene &scene)
{
	return vec3(
		(info.collisionNormal.x() + 1.f) / 2.f,
		(info.collisionNormal.y() + 1.f) / 2.f,
		(info.collisionNormal.z() + 1.f) / 2.f);
}

vec3 diffuseHardShadowedShader(const Ray &ray, const CollisionInfo &info, const Scene &scene)
{
	vec3 color(0.f, 0.f, 0.f); //Start with black.

	for (const PointLight &light : scene.pointLightList) {
		//Make ray to light
		Ray shadowTestRay;
		shadowTestRay.mask = CASTS_SHADOWS_BIT;
		shadowTestRay.origin = info.collisionPoint + SURFACE_DELTA * info.collisionNormal;
		shadowTestRay.dir = light.pos - shadowTestRay.origin;
		float lightDist2 = shadowTestRay.dir.dot(shadowTestRay.dir);
		shadowTestRay.dir.normalize();
		float geomFactor = shadowTestRay.dir.dot(info.collisionNormal);
		if (geomFactor < 0) {
			//Facing away from light source
			break;
		}

		CollisionInfo shadowTestInfo = scene.collide(shadowTestRay);

		if (shadowTestInfo.collisionOccurred == true) {
			//Need to check if collision occurs before light along ray.
			if (lightDist2 > shadowTestInfo.squaredDistance) {
				//Surface point is in shadow. Look at next light source.
				break;
			}
		}


		//Point not in shadow. Add contribution of light.
		color += geomFactor * light.power / lightDist2;
	}

	color = color.cwiseProduct(info.collidedObject->color);

	return color;
}

float radius = 0.01f;
float oneOverArea = 1 / (M_PI * radius * radius);

vec3 diffuseHardShadowedShaderCaustics(const Ray &ray, const CollisionInfo &info, const Scene &scene)
{
	vec3 color(0.f, 0.f, 0.f); //Start with black.

	for (const PointLight &light : scene.pointLightList) {
		//Make ray to light
		Ray shadowTestRay;
		shadowTestRay.mask = CASTS_SHADOWS_BIT;
		shadowTestRay.origin = info.collisionPoint + SURFACE_DELTA * info.collisionNormal;
		shadowTestRay.dir = light.pos - shadowTestRay.origin;
		float lightDist2 = shadowTestRay.dir.dot(shadowTestRay.dir);
		shadowTestRay.dir.normalize();
		float geomFactor = shadowTestRay.dir.dot(info.collisionNormal);
		if (geomFactor < 0) {
			//Facing away from light source
			break;
		}

		CollisionInfo shadowTestInfo = scene.collide(shadowTestRay);

		if (shadowTestInfo.collisionOccurred == true) {
			//Need to check if collision occurs before light along ray.
			if (lightDist2 > shadowTestInfo.squaredDistance) {
				//Surface point is in shadow. Look at next light source.
				break;
			}
		}


		//Point not in shadow. Add contribution of light.
		color += geomFactor * light.power / lightDist2;
	}

	color = color.cwiseProduct(info.collidedObject->color);

	//TEMP hacky caustic rendering.
	std::vector<const Photon*> photons;
	std::vector<float> dists;
	size_t n = 5;
	float k = 5.0f;

	scene.causticPhotonMap.getNNearestPhotons(info.collisionPoint, n, &photons, &dists);
	if (photons.size() != 0) {
		float maxdist = 0.f;
		for (size_t i = 0; i < photons.size(); ++i) {
			if (dists[i] > maxdist) maxdist = dists[i];
		}
		//Using cone filtering.
		if (maxdist > 0.f) {
			//float oneOverArea = 1.f / (M_PI * maxdist * maxdist);
			float denom = 1.f / ((1.f - 2.f/(3.f*k))*(M_PI * maxdist * maxdist));
			for (size_t i = 0; i < photons.size(); ++i) {

				float dotProd = photons[i]->ray.dir.dot(info.collisionNormal);
				if (dotProd > 0.f) {
					//color += oneOverArea * dotProd * photons[i]->power.cwiseProduct(info.collidedObject->color);
					color += denom * dotProd * photons[i]->power.cwiseProduct(info.collidedObject->color) * (1.f - (dists[i]/(k*maxdist)));
				}

				//color += radius * 0.001f * photons[i]->power / dists[i];

			}
		}
	}

	return color;
}

glue::vec3 perfectMirrorShader(const Ray &ray, const CollisionInfo &info, const Scene &scene)
{
	//Make reflected ray.
	Ray reflectedRay;
	reflectedRay.depth = ray.depth + 1;
	reflectedRay.origin = info.collisionPoint + SURFACE_DELTA * info.collisionNormal;
	vec3 incident = ray.dir;
	reflectedRay.dir = incident - 2 * info.collisionNormal * (incident.dot(info.collisionNormal));
	return scene.trace(reflectedRay);
}

float internalRI = 1.5f;
float externalRI = 1.f;

glue::vec3 refractShader(const Ray &ray, const CollisionInfo &info, const Scene &scene)
{
	Ray refractedRay;
	refractedRay.dir = refract(ray.dir, info.collisionNormal, internalRI);
	refractedRay.origin = info.collisionPoint + SURFACE_DELTA*refractedRay.dir;
	refractedRay.depth = ray.depth + 1;

	return scene.trace(refractedRay);

	//TODO: Total internal reflection
}

glue::vec3 refractShaderFresnel(const Ray &ray, const CollisionInfo &info, const Scene &scene)
{
	Ray refractedRay;
	float reflectance = fresnelReflectance(ray.dir, info.collisionNormal, internalRI);
	refractedRay.dir = refract(ray.dir, info.collisionNormal, internalRI);
	vec3 reflectionContribution(0.f, 0.f, 0.f);
	if (reflectance > 0.f) {
		reflectionContribution = reflectance * perfectMirrorShader(ray, info, scene);
	}
	if (reflectance == 1.f) {
		return reflectionContribution;
	}
	refractedRay.origin = info.collisionPoint + SURFACE_DELTA*refractedRay.dir;
	refractedRay.depth = ray.depth + 1;

	vec3 refractionContribution = (1.f - reflectance) * scene.trace(refractedRay);
	return reflectionContribution + refractionContribution;
}

vec3 simpleColorShader(const Ray &ray, const CollisionInfo &info, const Scene &scene)
{
	return info.collidedObject->color;
}
