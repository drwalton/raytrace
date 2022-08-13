#include "raytrace/CameraModelPinhole.hpp"
#include <Eigen/Dense>

using namespace glue;

CameraModelPinhole::CameraModelPinhole(size_t width, size_t height, 
		float cx, float cy, float fx, float fy)
	:CameraModel(width, height), cx_(cx), cy_(cy), fx_(fx), fy_(fy)
{
	K_ << 
		fx_, 0, cx_,
		0, fy_, cy_,
		0, 0, 1;
	Kinv_ = K_.inverse();
}

CameraModelPinhole::~CameraModelPinhole() throw()
{}

Ray CameraModelPinhole::imToRay(const glue::mat4 &poseInv, size_t x, size_t y) const
{
	Ray ray;

	vec4 origin4 = poseInv * vec4(0,0,0,1);
	ray.origin = vec3(origin4.x(), origin4.y(), origin4.z());
	vec3 dirCam = Kinv_ * vec3(float(x), float(y), 1);
	ray.dir = poseInv.block<3,3>(0,0) * vec3(dirCam.x(), dirCam.y(), -dirCam.z());

	return ray;
}

glue::vec2 CameraModelPinhole::worldToIm(const glue::mat4 &pose, const glue::vec3 &worldPos) const
{
	vec4 worldPos4(worldPos.x(), worldPos.y(), worldPos.z(), 1.f);
	vec4 camPos4 = pose * worldPos4;
	vec3 camPos(camPos4.x(), camPos4.y(), -camPos4.z());
	vec3 imPos3 = K_ * camPos;
	return vec2(imPos3.x() / imPos3.z(), imPos3.y() / imPos3.z());
}
