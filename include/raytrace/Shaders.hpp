#ifndef RAYTRACE_SHADERS_HPP_INCLUDED
#define RAYTRACE_SHADERS_HPP_INCLUDED

#include <glue/VectorTypes.hpp>

struct Ray;
struct CollisionInfo;
class Scene;

///\brief This shader sets the output colour according to the normal at the collision.
glue::vec3 defaultShader(const Ray &ray, const CollisionInfo &info, const Scene &scene);

///\brief Diffuse material shader which performs a binary shadow test.
glue::vec3 diffuseHardShadowedShader(const Ray &ray, const CollisionInfo &info, const Scene &scene);

glue::vec3 diffuseHardShadowedShaderCaustics(const Ray &ray, const CollisionInfo &info, const Scene &scene);

///\brief Shader implementing perfect mirror reflection
glue::vec3 perfectMirrorShader(const Ray &ray, const CollisionInfo &info, const Scene &scene);

///\brief Simple shader for perfect refraction.
glue::vec3 refractShader(const Ray &ray, const CollisionInfo &info, const Scene &scene);

///\brief Shader that combines results from refracted and reflected rays according to the Fresnel equations.
glue::vec3 refractShaderFresnel(const Ray &ray, const CollisionInfo &info, const Scene &scene);

///\brief Returns color assigned to collided object.
glue::vec3 simpleColorShader(const Ray &ray, const CollisionInfo &info, const Scene &scene);

#endif
