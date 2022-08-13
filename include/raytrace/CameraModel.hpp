#ifndef RAYTRACE_CAMERAMODEL_HPP_INCLUDED
#define RAYTRACE_CAMERAMODEL_HPP_INCLUDED

#include "Ray.hpp"

class CameraModel {
public:
	explicit CameraModel(size_t width, size_t height);
	virtual ~CameraModel() throw();

	virtual Ray imToRay(const glue::mat4 &poseInv, size_t x, size_t y) const = 0;
	virtual glue::vec2 worldToIm(const glue::mat4 &pose, const glue::vec3 &worldPos) const = 0;

	size_t width() const { return width_; }
	size_t height() const { return height_; }
protected:
	size_t width_, height_;
};

#endif
