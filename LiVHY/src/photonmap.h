#pragma once
#include "scene.h"
#include "nanoflann-1.4.3/nanoflann.hpp"

struct Photon
{
	Vec3 position;
	unsigned char rgbe[4]; //https://en.wikipedia.org/wiki/RGBE_image_format
	Vec3 direction; //TODO possibly turn into lookuptable index

	Photon(Vec3 pos, Vec3 dir)
		: position(pos), direction(dir)
	{
	}
};

//template <typename T>
struct PhotonCloud
{
	std::vector<Photon*> pts;

	// Must return the number of data points
	inline size_t kdtree_get_point_count() const { return pts.size(); }

	// Returns the dim'th component of the idx'th point in the class:
	inline double kdtree_get_pt(const size_t idx, const size_t dim) const
	{
		return pts[idx]->position[(glm::vec<3,double,glm::packed_highp>::length_type)dim];
	}

	// Optional bounding-box computation: return false to default to a standard
	// bbox computation loop.
	//   Return true if the BBOX was already computed by the class and returned
	//   in "bb" so it can be avoided to redo it again. Look at bb.size() to
	//   find out the expected dimensionality (e.g. 2 or 3 for point clouds)
	template <class BBOX>
	bool kdtree_get_bbox(BBOX& /* bb */) const
	{
		return false;
	}
};

enum class PhotonType
{
	None,
	Global,
	Caustic
};

//inline std::vector<Photon*> g_GlobalPhotons;
//inline std::vector<Photon*> g_CausticPhotons;
inline PhotonCloud g_GlobalPhotons;
inline PhotonCloud g_CausticPhotons;

using PhotonMapTree = nanoflann::KDTreeSingleIndexAdaptor<
	nanoflann::L2_Simple_Adaptor<double, PhotonCloud>,
	PhotonCloud, 3>;

inline PhotonMapTree* g_GlobalPhotonMap = nullptr;
inline PhotonMapTree* g_CausticPhotonMap = nullptr;


void ClearMaps();

void RNRgb_to_RGBE(RGB& rgb_src, unsigned char* rgbe_target);

void AddPhoton(RGB photon, std::vector<Photon*>& photonStorage, const HitInfo& hitInfo, PhotonType type);

void TracePhoton(const Scene& scene, Ray ray, RGB photon, std::vector<Photon*>& photonStorage, PhotonType type, int photonCount);

void EmitPhotons(const Scene& scene, const Light* light, PhotonType type, int count);

void PhotonTracer(const Scene& scene, const int globalNum, const int causticNum,
				  const std::vector<double>& lightPowers, const double totalPower);

void MapPhotons(const Scene& scene);

