#include "Object.hpp"
#include "Vector.hpp"
#include "Bounds3.hpp"
#include "Material.hpp"
#include "Rect.hpp"
#include <math.h>

const float ZETA = 0.005;

class Box : public Object {
public:
    Bounds3 b;
    Material *m;
    float y_rotation;
    Box() {}
    Box(const Vector3f p1, Vector3f p2, float y_rot) 
    : y_rotation(y_rot), m(new Material()){
        b = Bounds3(p1, p2);
    }

    Ray rotateRay(const Ray& ray) const{
        Vector3f center = (b.pMin+b.pMax)/2;
        Vector3f orig = (ray.origin - center);
        orig.x = orig.x * std::cos(y_rotation*M_PI / 180.) + orig.z * std::sin(y_rotation*M_PI / 180.);
        orig.z = - orig.x * std::sin(y_rotation*M_PI / 180.) + orig.z * std::cos(y_rotation*M_PI / 180.);
        orig += center;
        Vector3f dir = (ray.origin - center);
        dir.x = dir.x * std::cos(y_rotation*M_PI / 180.) + dir.z * std::sin(y_rotation*M_PI / 180.);
        dir.z = - dir.x * std::sin(y_rotation*M_PI / 180.) + dir.z * std::cos(y_rotation*M_PI / 180.);
        dir += center;
        Ray r(orig, dir);
        r.t_min = ray.t_min;
        r.t_max = ray.t_max;
        return r;
    }
    Vector3f rotateBack(const Vector3f v){
        Vector3f center = (b.pMin+b.pMax)/2;
        Vector3f vec = (v - center);
        vec.x = vec.x * std::cos(-y_rotation*M_PI / 180.) + vec.z * std::sin(-y_rotation*M_PI / 180.);
        vec.z = - vec.x * std::sin(-y_rotation*M_PI / 180.) + vec.z * std::cos(-y_rotation*M_PI / 180.);
        vec += center;
        return vec;
    }

    bool intersect(const Ray& ray) {
        Ray r = ray;//rotateRay(ray);
        std::array<int, 3> dirIsNeg;
        return b.IntersectP(r, r.direction_inv, dirIsNeg);
    }
    bool intersect(const Ray &ray, float &tnear, uint32_t &index) const {
        Ray r = ray; //rotateRay(ray);
        std::array<int, 3> dirIsNeg;
        return b.IntersectP(r, r.direction_inv, dirIsNeg);
    }
    Intersection getIntersection(Ray _ray) {
        Intersection inter;
        Ray r = _ray;//rotateRay(_ray);

        float tMin = (b.pMin.x - r.origin.x) * r.direction_inv.x;
        float tMax = (b.pMax.x - r.origin.x) * r.direction_inv.x;
        if(tMin > tMax) std::swap(tMin, tMax);
        float yMin = (b.pMin.y - r.origin.y) * r.direction_inv.y;
        float yMax = (b.pMax.y - r.origin.y) * r.direction_inv.y;
        if(yMin > yMax) std::swap(yMin, yMax);
        float zMin = (b.pMin.z - r.origin.z) * r.direction_inv.z;
        float zMax = (b.pMax.z - r.origin.z) * r.direction_inv.z;
        if(zMin > zMax) std::swap(zMin, zMax);

        if(tMin > yMax || yMin > tMax) return inter;
        if(yMin > tMin) tMin = yMin;
        if(yMax < tMax) tMax = yMax;

        if(tMin > zMax || zMin > tMax) return inter;
        if(zMin > tMin) tMin = zMin;
        if(zMax < tMax) tMax = zMax;

        Vector3f point = r.origin + tMin * r.direction;
        Vector3f normal;
        if(abs(point.x - b.pMin.x) < ZETA) normal = Vector3f(-1,0,0);
        else if(abs(point.x - b.pMax.x) < ZETA) normal = Vector3f(1,0,0);
        else if(abs(point.y - b.pMin.y) < ZETA) normal = Vector3f(0,-1,0);
        else if(abs(point.y - b.pMax.y) < ZETA) normal = Vector3f(0,1,0);
        else if(abs(point.z - b.pMin.z) < ZETA) normal = Vector3f(0,0,-1);
        else if(abs(point.z - b.pMax.z) < ZETA) normal = Vector3f(0,0,1);

        // point = rotateBack(point);
        // normal = normalize(rotateBack(normal));
        // normal = Vector3f(0,0,1);

        Vector3f diff = point - r.origin;
		float dist = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

        inter.obj = dynamic_cast<Object*>(this);
        inter.m = this->m;
        inter.happened = true;
        inter.normal = normal;
        inter.coords = point + normal * 0.001;
        inter.distance = dist;

        return inter;
    }
    void getSurfaceProperties(const Vector3f &P, const Vector3f &I, const uint32_t &index, const Vector2f &uv, Vector3f &N, Vector2f &st) const{
        // if(P.x == b.pMin.x) N = Vector3f(1,0,0);
        // else if(P.x == b.pMax.x) N = Vector3f(-1,0,0);
        // else if(P.y == b.pMin.y) N = Vector3f(0,1,0);
        // else if(P.y == b.pMax.y) N = Vector3f(0,-1,0);
        // else if(P.z == b.pMin.z) N = Vector3f(0,0,1);
        // else if(P.z == b.pMax.z) N = Vector3f(0,0,-1);
    }
    Vector3f evalDiffuseColor(const Vector2f &st) const {
        return m->getColor();
    }
    Bounds3 getBounds() {return b;}

};