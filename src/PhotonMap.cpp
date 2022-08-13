#include "raytrace/PhotonMap.hpp"
#include "raytrace/CameraModel.hpp"
#include <flann/flann.hpp>

using namespace glue;

struct PhotonMap::Impl
{
	std::vector<Photon> photonList;
	std::vector<glue::vec3> posList;
	std::unique_ptr<flann::Index<flann::L2<float> > > nnIndex;
	Impl() {}
	~Impl() {}
	void addPhoton(const Photon &photon) {
		photonList.push_back(photon);
		posList.push_back(photon.ray.origin);
	}

	void buildIndex() {
		flann::Matrix<float> listMat(reinterpret_cast<float*>(posList.data()),
			posList.size(), 3);
		nnIndex.reset(new flann::Index<flann::L2<float> >(listMat, flann::KDTreeIndexParams(4)));
		nnIndex->buildIndex();
	}

	void getPhotonsInRadius(const glue::vec3 &pos, float radius,
		std::vector<const Photon*> *photons, std::vector<float> *dists)
	{
		if (nnIndex == nullptr) {
			buildIndex();
		}
		flann::Matrix<float> query(const_cast<float*>(&pos.x()), 1, 3);
		std::vector<std::vector<float>> distsVec;
		std::vector<std::vector<int>> indicesVec;
		flann::SearchParams params;
		int numFound = nnIndex->radiusSearch(query, indicesVec, distsVec, radius, params);
		if (numFound > 0) {
			photons->resize(indicesVec[0].size());
			dists->resize(indicesVec[0].size());

			for (size_t i = 0; i < indicesVec[0].size(); ++i) {
				(*photons)[i] = (&photonList[0]) + indicesVec[0][i];
				(*dists)[i] = distsVec[0][i];
			}
		}
	}
	void getNNearestPhotons(const glue::vec3 &pos, size_t n,
		std::vector<const Photon*> *photons, std::vector<float> *dists)
	{
		if (nnIndex == nullptr) {
			buildIndex();
		}
		flann::Matrix<float> query(const_cast<float*>(&pos.x()), 1, 3);
		std::vector<std::vector<float>> distsVec;
		std::vector<std::vector<int>> indicesVec;
		flann::SearchParams params;
		int numFound = nnIndex->knnSearch(query, indicesVec, distsVec, n, params);
		if (numFound > 0) {
			photons->resize(indicesVec[0].size());
			dists->resize(indicesVec[0].size());

			for (size_t i = 0; i < indicesVec[0].size(); ++i) {
				(*photons)[i] = (&photonList[0]) + indicesVec[0][i];
				(*dists)[i] = distsVec[0][i];
			}
		}
	}
};

PhotonMap::PhotonMap()
:pimpl_(new Impl)
{}

PhotonMap::~PhotonMap() throw()
{}

void PhotonMap::addPhoton(const Photon &photon)
{
	pimpl_->addPhoton(photon);
}

void PhotonMap::getPhotonsInRadius(const glue::vec3 &pos, float radius,
	std::vector<const Photon*> *photons, std::vector<float> *dists) const
{
	pimpl_->getPhotonsInRadius(pos, radius, photons, dists);
}
void PhotonMap::getNNearestPhotons(const glue::vec3 &pos, size_t n,
	std::vector<const Photon*> *photons, std::vector<float> *dists) const
{
	pimpl_->getNNearestPhotons(pos, n, photons, dists);
}

size_t PhotonMap::size() const
{
	return pimpl_->photonList.size();
}

void PhotonMap::visualize(const CameraModel *camModel, const glue::mat4 pose, float *image)
{
	for (const Photon &p : pimpl_->photonList) {
		vec2 imPos = camModel->worldToIm(pose, p.ray.origin);
		size_t x = floor(imPos.x()), y = floor(imPos.y());
		if (x < camModel->width() && y < camModel->height()) {
			image[x * 3 + y*camModel->width() * 3 + 0] = 1.f;
			image[x * 3 + y*camModel->width() * 3 + 1] = 1.f;
			image[x * 3 + y*camModel->width() * 3 + 2] = 1.f;
		}
		//std::cout << p.ray.origin << std::endl;
	}
}
