#include "pch.h"
#include "triangleMesh.h"

/// faces should contain triples of indices describing a single triangle face.
TriangleMesh::TriangleMesh(const std::vector<Vec3>& vertices, const std::vector<Vec3i> faces, const Material* material, bool cull, bool samplingTarget)
	: Object(material, cull, samplingTarget)
{
	for(const Vec3i& face : faces)
	{
		m_Triangles.push_back(new Triangle(vertices[face[0]], vertices[face[1]], vertices[face[2]], material, cull));
	}
}

TriangleMesh::TriangleMesh(const std::string& objectName, const Material* material, bool cull, bool samplingTarget)
	: Object(material, cull, samplingTarget)
{
	std::ifstream in;
	in.open("./assets/models/" + objectName + ".obj", std::ifstream::in);
	if(in.fail())
		return;

	std::vector<Vec3i> faces;
	std::vector<Vec3> verts;

	std::string line;

	while(!in.eof())
	{
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		std::string trash;
		if(!line.compare(0, 2, "v "))
		{
			iss >> trash;
			Vec3 v;
			for(int i = 0; i < 3; i++)
			{
				iss >> v[i];
			}
			verts.push_back(v);
		}
		else if(!line.compare(0, 2, "f "))
		{
			int a, b, c;
			iss >> trash >> a >> trash >> b >> trash >> c >> trash;
			a--; // in wavefront obj all indices start at 1, not zero
			b--;
			c--;
			faces.push_back({a,b,c});
		}
	}
	for(const Vec3i& face : faces)
	{
		m_Triangles.push_back(new Triangle(verts[face[0]], verts[face[1]], verts[face[2]], material, cull));
	}
}

TriangleMesh::~TriangleMesh()
{
	for(Object*& obj : m_Triangles)
	{
		delete obj;
	}
}

const std::vector<Object*>& TriangleMesh::Triangles() const
{
	return m_Triangles;
}

bool TriangleMesh::Hit(const Ray& ray, double tMin, double tMax, HitInfo& hitInfo) const
{
	HitInfo auxInfo;
	bool hasHit = false;
	double hitDist = tMax;

	for(const auto& obj : m_Triangles)
	{
		if(obj->Hit(ray, tMin, hitDist, auxInfo))
		{
			hasHit = true;
			hitDist = auxInfo.t;
			hitInfo = auxInfo;
		}
	}

	return hasHit;
}

bool TriangleMesh::BoundingBox(AABB& outputBox) const
{
	if(m_Triangles.empty()) return false;

	AABB auxBox;
	bool firstBox = true;

	for(const auto& obj : m_Triangles)
	{
		if(!obj->BoundingBox(auxBox)) return false;

		if(firstBox)
		{
			outputBox = auxBox;
			firstBox = false;
		}
		else
		{
			outputBox.Surround(auxBox);
		}
	}

	return true;
}

TriangleMesh::TriangleMesh(const Material* material, bool cull, bool samplingTarget)
	: Object(material, cull, samplingTarget)
{
}
