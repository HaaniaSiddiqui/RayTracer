#include <iostream>
#include <sstream>
#include "Bbox.hpp"
#include "Point3D.hpp"
#include "../geometry/Geometry.hpp"
#include "Ray.hpp"

BBox::BBox(const Point3D &min, const Point3D &max) : pmin(min), pmax(max) {}

std::string BBox::to_string() const
{
    std::stringstream sstream;
    sstream << "The minimum point is -> (" << pmin.x << "," << pmin.y << "," << pmin.z << ")" << std::endl;
    sstream << "The maximum point is -> (" << pmax.x << "," << pmax.y << "," << pmax.z << ")" << std::endl;
    return sstream.str();
}

bool BBox::hit(const Ray &ray, float &t_enter, float &t_exit) const
{
    Vector3D invD(1 / ray.d.x, 1 / ray.d.y, 1 / ray.d.z);

    Vector3D t0s = (this->pmin - ray.o) * invD;
    Vector3D t1s = (this->pmax - ray.o) * invD;

    double tminx, tminy, tminz, tmaxx, tmaxy, tmaxz;

    tminx = std::min(t0s.x, t1s.x);
    tminy = std::min(t0s.y, t1s.y);
    tminz = std::min(t0s.z, t1s.z);
    tmaxx = std::max(t0s.x, t1s.x);
    tmaxy = std::max(t0s.y, t1s.y);
    tmaxz = std::max(t0s.z, t1s.z);

    t_enter = std::max(tminx, std::max(tminy, tminz));
    t_exit = std::min(tmaxx, std::min(tmaxy, tmaxz));

    return t_enter < t_exit;
}

// TODO
void BBox::extend(Geometry *g)
{
}

// TODO
void BBox::extend(const BBox &b)
{
}

bool BBox::contains(const Point3D &p) const
{
    return (p.x >= pmin.x && p.x <= pmax.x) && (p.y >= pmin.y && p.y <= pmax.y) && (p.z >= pmin.z && p.z <= pmax.z);
}

bool BBox::overlaps(Geometry *g)
{
    BBox gBox = g->getBBox();

    return this->overlaps(gBox);
}

bool BBox::overlaps(const BBox &b)
{
    int result = 0;

    if (b.pmin.x <= this->pmax.x && b.pmax.x >= this->pmin.x)
        result++;

    if (b.pmin.y <= this->pmax.y && b.pmax.y >= this->pmin.y)
        result++;

    if (b.pmin.z <= this->pmax.z && b.pmax.z >= this->pmin.z)
        result++;

    return result == 3;
}
