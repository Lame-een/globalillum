#pragma once
#include "util/types.h"
#include <vector>

class Object;

class PDF
{
public:
	virtual double Value(const Vec3& dir) const = 0;
	virtual Vec3 Generate() const = 0;
};

class CosinePDF : public PDF {
    public:
        CosinePDF(const Vec3& normal);

        double Value(const Vec3& dir) const override;

        Vec3 Generate() const override;

		const ONB& Base();
    private:
        ONB m_Base;
};

class SpecularPDF : public PDF {
    public:
        SpecularPDF(const Vec3& normal, double shininess);

        double Value(const Vec3& dir) const override;

        Vec3 Generate() const override;

		const ONB& Base();
    private:
        ONB m_Base;
        double m_Shininess;
};

class ObjectsPDF : public PDF
{
public:
	ObjectsPDF(const Vec3& origin);

	double Value(const Vec3& dir) const override;
	Vec3 Generate() const override;

	void AddObject(const Object* obj);
	void AddObject(const std::vector<Object*>& objs);

public:
	Vec3 m_Origin;
	std::vector<const Object*> m_Objects;
};

class MixturePDF : public PDF
{
public:
	MixturePDF(const PDF* material, const PDF* tgt, bool cleanup = false);
	~MixturePDF();

	double Value(const Vec3& dir) const override;

	Vec3 Generate() const override;

public:
	const PDF* m_MaterialPdf;
	const PDF* m_TargetsPdf;
	
	bool m_Cleanup;
};