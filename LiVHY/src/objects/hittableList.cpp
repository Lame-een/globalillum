#include "hittableList.h"

HittableList::HittableList()
{
}

void HittableList::Add(Hittable* obj)
{
    m_List.push_back(obj);
}

std::vector<Hittable*>&  HittableList::List()
{
    return m_List;
}

void HittableList::Clear()
{
    m_List.clear();
}

bool HittableList::Hit(const Ray& ray, const double& near, const double& far, HitInfo& hitInfo)
{
    HitInfo auxInfo;
    bool hasHit = false;
    double hitDistance = far;

    for (const auto& obj : m_List) {
        if (obj->Hit(ray, near, hitDistance, auxInfo)) {
            hasHit = true;
            hitDistance = auxInfo.t;
            hitInfo = auxInfo;
        }
    }

    return hasHit;
}

bool HittableList::BoundingBox(AABB& outputBox) const
{
    if (m_List.empty()) return false;

    AABB auxBox;
    bool firstBox = true;

    for (const auto& obj : m_List) {
        if (!obj->BoundingBox(auxBox)) return false;

        if(firstBox){
            outputBox = auxBox;
            firstBox = false;
        }else{
            outputBox.Surround(auxBox);
        }
    }

    return true;
}
