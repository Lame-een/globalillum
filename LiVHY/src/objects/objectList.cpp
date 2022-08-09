#include "ObjectList.h"

ObjectList::ObjectList()
{
}

void ObjectList::Add(Object* obj)
{
    m_List.push_back(obj);
}

std::vector<Object*>&  ObjectList::List()
{
    return m_List;
}

const std::vector<Object*>&  ObjectList::List() const
{
    return m_List;
}

void ObjectList::Clear()
{
    m_List.clear();
}

bool ObjectList::Hit(const Ray& ray, const double& tMin, const double& tMax, HitInfo& hitInfo)
{
    HitInfo auxInfo;
    bool hasHit = false;
    double hitDistance = tMax;

    for (const auto& obj : m_List) {
        if (obj->Hit(ray, tMin, hitDistance, auxInfo)) {
            hasHit = true;
            hitDistance = auxInfo.t;
            hitInfo = auxInfo;
        }
    }

    return hasHit;
}

bool ObjectList::BoundingBox(AABB& outputBox) const
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
