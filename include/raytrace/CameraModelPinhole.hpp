#ifndef RAYTRACE_CAMERAMODELPINHOLE_HPP_INCLUDED
#define RAYTRACE_CAMERAMODELPINHOLE_HPP_INCLUDED

#include "CameraModel.hpp"

class CameraModelPinhole : public CameraModel {
public:
	CameraModelPinhole(size_t width, size_t height, 
		float cx, float cy, float fx, float fy);
	virtual ~CameraModelPinhole() throw();

	virtual Ray imToRay(const glue::mat4 &poseInv, size_t x, size_t y) const;
	virtual glue::vec2 worldToIm(const glue::mat4 &pose, const glue::vec3 &worldPos) const;
private:
	float cx_, cy_, fx_, fy_;
	glue::mat3 K_, Kinv_;
};

#endif
