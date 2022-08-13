#ifndef RAYTRACE_PHOTONMAP_HPP_INCLUDED
#define RAYTRACE_PHOTONMAP_HPP_INCLUDED

#include "Photon.hpp"
#include <memory>

class CameraModel;

class PhotonMap final
{
public:
	PhotonMap();
	~PhotonMap() throw();

	void addPhoton(const Photon &photon);
	void getPhotonsInRadius(const glue::vec3 &pos, float radius,
		std::vector<const Photon*> *photons, std::vector<float> *dists) const;
	void getNNearestPhotons(const glue::vec3 &pos, size_t n,
		std::vector<const Photon*> *photons, std::vector<float> *dists) const;

	size_t size() const;

	///\brief Debug function for visualising locations of photons on an image.
	void visualize(const CameraModel *camModel, const glue::mat4 pose, float *image);

private:
	struct Impl;
	std::unique_ptr<Impl> pimpl_;
};

#endif
