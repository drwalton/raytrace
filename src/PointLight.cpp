#include "raytrace/PointLight.hpp"

PointLight::PointLight(const glue::vec3 &pos, const glue::vec3 &power)
	:pos(pos), power(power)
{}
