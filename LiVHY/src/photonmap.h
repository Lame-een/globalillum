#pragma once
#include "scene.h"

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

enum class PhotonType
{
	None,
	Global,
	Caustic
};

inline std::vector<Photon*> g_GlobalPhotons;
inline std::vector<Photon*> g_CausticPhotons;

void ClearMaps();

void RNRgb_to_RGBE(RGB& rgb_src, unsigned char* rgbe_target);

void AddPhoton(RGB photon, std::vector<Photon*>& photonStorage, const HitInfo& hitInfo, PhotonType type);

void TracePhoton(const Scene& scene, Ray ray, RGB photon, std::vector<Photon*>& photonStorage, PhotonType type, int photonCount);

void EmitPhotons(const Scene& scene, const Light* light, PhotonType type, int count);

void PhotonTracer(const Scene& scene, const int globalNum, const int causticNum,
				  const std::vector<double>& lightPowers, const double totalPower);

void MapPhotons(const Scene& scene);

