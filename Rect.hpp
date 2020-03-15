#include "Object.hpp"
#include "Vector.hpp"
#include "Bounds3.hpp"
#include "Material.hpp"

class Rect_xy : public Object {
public:
    float x0, x1, y0, y1, z;
    Bounds3 bounds;
    Material *m;
    Rect_xy(float _x0, float _x1, float _y0, float _y1, float _z)
        : x0(_x0), x1(_x1), y0(_y0), y1(_y1), z(_z), m(new Material()) {
            bounds = Bounds3(Vector3f(x0, y0, z - 0.0001f), Vector3f(x1, y1, z + 0.0001f));
        }
    bool intersect(const Ray &ray) {
        std::cout << "intersect 1\n";
        std::array<int, 3> dirIsNeg;
        return bounds.IntersectP(ray, ray.direction_inv, dirIsNeg);
    }
    bool intersect(const Ray &ray, float &tnear, uint32_t &index) const {
        std::cout << "intersect 2\n";
        std::array<int, 3> dirIsNeg;
        return bounds.IntersectP(ray, ray.direction_inv, dirIsNeg);
    }
    Intersection getIntersection(Ray ray) {
        // std::cout << "getIntersection\n";
        Intersection inter;

        std::array<float, 3> pMin = {fmin(x0, x1), fmin(y0, y1), z - 0.0001f};
        std::array<float, 3> pMax = {fmax(x0, x1), fmax(y0, y1), z + 0.0001f};
        // auto pMax = Vector3f(fmax(x0, x1), fmax(y0, y1), z);

        float t0 = 0, t1 = ray.t_max;
        
        float invRayX = ray.direction_inv.x;
        float tNear = (bounds.pMin.x - ray.origin.x) * invRayX;
        float tFar = (bounds.pMax.x - ray.origin.x) * invRayX;
        if (tNear > tFar)
            std::swap(tNear, tFar);
        t0 = tNear > t0 ? tNear : t0;
        t1 = tFar < t1 ? tFar : t1;
        if (t0 > t1)
            return inter;
        float invRayY = ray.direction_inv.y;
        tNear = (bounds.pMin.y - ray.origin.y) * invRayY;
        tFar = (bounds.pMax.y - ray.origin.y) * invRayY;
        if (tNear > tFar)
            std::swap(tNear, tFar);
        t0 = tNear > t0 ? tNear : t0;
        t1 = tFar < t1 ? tFar : t1;
        if (t0 > t1)
            return inter;
        float invRayZ = ray.direction_inv.z;
        tNear = (bounds.pMin.z - ray.origin.z) * invRayZ;
        tFar = (bounds.pMax.z - ray.origin.z) * invRayZ;
        if (tNear > tFar)
            std::swap(tNear, tFar);
        t0 = tNear > t0 ? tNear : t0;
        t1 = tFar < t1 ? tFar : t1;
        if (t0 > t1)
            return inter;

        // for (int i = 0; i < 3; i++) {
        //     float invRay = ray.direction_inv[i];
        //     float tNear = (pMin[i] - ray.origin[i]) * invRay;
        //     float tFar = (pMax[i] - ray.origin[i]) * invRay;
        //     if (tNear > tFar)
        //         std::swap(tNear, tFar);
        //     t0 = tNear > t0 ? tNear : t0;
        //     t1 = tFar < t1 ? tFar : t1;
        //     if (t0 > t1)
        //         return inter;
        // }

        inter.obj = dynamic_cast<Object*>(this);
        inter.m = this->m;
        inter.happened = true;
        inter.normal = Vector3f(0, 0, 1);
        inter.coords = t0 * ray.direction + ray.origin;
        inter.distance = t0;

        return inter;
    }
    void getSurfaceProperties(const Vector3f &P, const Vector3f &I, const uint32_t &index, const Vector2f &uv, Vector3f &N, Vector2f &st) const {
        // std::cout << "getSurfaceProperties\n";
        // N = Vector3f(0, 0, 1);
		N = P.z - z > 0 ? Vector3f(0, 0, 1) : Vector3f(0, 0, -1);
        // st = Vector2f(0, 1);
    }
    Vector3f evalDiffuseColor(const Vector2f &st) const {
        return m->getColor();
    }
    Bounds3 getBounds() {return bounds;}
};

class Rect_xz : public Object {
public:
    float x0, x1, z0, z1, y;
    Bounds3 bounds;
    Material *m;
    Rect_xz(float _x0, float _x1, float _z0, float _z1, float _y)
        : x0(_x0), x1(_x1), z0(_z0), z1(_z1), y(_y), m(new Material()) {
            bounds = Bounds3(Vector3f(x0, y - 0.0001f, z0), Vector3f(x1, y + 0.0001f, z1));
        }
    bool intersect(const Ray &ray) {
        std::cout << "intersect 1\n";
        std::array<int, 3> dirIsNeg;
        return bounds.IntersectP(ray, ray.direction_inv, dirIsNeg);
    }
    bool intersect(const Ray &ray, float &tnear, uint32_t &index) const {
        std::cout << "intersect 2\n";
        std::array<int, 3> dirIsNeg;
        return bounds.IntersectP(ray, ray.direction_inv, dirIsNeg);
    }
    Intersection getIntersection(Ray ray) {
        // std::cout << "getIntersection\n";
        Intersection inter;

        std::array<float, 3> pMin = {fmin(x0, x1), y - 0.0001f, fmin(z0, z1)};
        std::array<float, 3> pMax = {fmax(x0, x1), y + 0.0001f, fmax(z0, z1)};
        // auto pMax = Vector3f(fmax(x0, x1), y, fmax(z0, z1));

        float t0 = 0, t1 = ray.t_max;
        
        float invRayX = ray.direction_inv.x;
        float tNear = (bounds.pMin.x - ray.origin.x) * invRayX;
        float tFar = (bounds.pMax.x - ray.origin.x) * invRayX;
        if (tNear > tFar)
            std::swap(tNear, tFar);
        t0 = tNear > t0 ? tNear : t0;
        t1 = tFar < t1 ? tFar : t1;
        if (t0 > t1)
            return inter;
        float invRayY = ray.direction_inv.y;
        tNear = (bounds.pMin.y - ray.origin.y) * invRayY;
        tFar = (bounds.pMax.y - ray.origin.y) * invRayY;
        if (tNear > tFar)
            std::swap(tNear, tFar);
        t0 = tNear > t0 ? tNear : t0;
        t1 = tFar < t1 ? tFar : t1;
        if (t0 > t1)
            return inter;
        float invRayZ = ray.direction_inv.z;
        tNear = (bounds.pMin.z - ray.origin.z) * invRayZ;
        tFar = (bounds.pMax.z - ray.origin.z) * invRayZ;
        if (tNear > tFar)
            std::swap(tNear, tFar);
        t0 = tNear > t0 ? tNear : t0;
        t1 = tFar < t1 ? tFar : t1;
        if (t0 > t1)
            return inter;

        // for (int i = 0; i < 3; i++) {
        //     float invRay = ray.direction_inv[i];
        //     float tNear = (pMin[i] - ray.origin[i]) * invRay;
        //     float tFar = (pMax[i] - ray.origin[i]) * invRay;
        //     if (tNear > tFar)
        //         std::swap(tNear, tFar);
        //     t0 = tNear > t0 ? tNear : t0;
        //     t1 = tFar < t1 ? tFar : t1;
        //     if (t0 > t1)
        //         return inter;
        // }

        inter.obj = dynamic_cast<Object*>(this);
        inter.m = this->m;
        inter.happened = true;
        inter.normal = Vector3f(0, 0, 1);
        inter.coords = t0 * ray.direction + ray.origin;
        inter.distance = t0;

        return inter;
    }
    void getSurfaceProperties(const Vector3f &P, const Vector3f &I, const uint32_t &index, const Vector2f &uv, Vector3f &N, Vector2f &st) const {
        // std::cout << "getSurfaceProperties\n";
        // N = Vector3f(0, 1, 0);
		N = P.y - y > 0 ? Vector3f(0, 1, 0) : Vector3f(0, -1, 0);
        // st = Vector2f(0, 1);
    }
    Vector3f evalDiffuseColor(const Vector2f &st) const {
        return m->getColor();
    }
    Bounds3 getBounds() {return bounds;}
};

class Rect_yz : public Object {
public:
    float y0, y1, z0, z1, x;
    Bounds3 bounds;
    Material *m;
    Rect_yz(float _y0, float _y1, float _z0, float _z1, float _x)
        : y0(_y0), y1(_y1), z0(_z0), z1(_z1), x(_x), m(new Material()) {
            bounds = Bounds3(Vector3f(x - 0.0001f, y0, z0), Vector3f(x + 0.0001f, y1, z1));
        }
    bool intersect(const Ray &ray) {
        std::cout << "intersect 1\n";
        std::array<int, 3> dirIsNeg;
        return bounds.IntersectP(ray, ray.direction_inv, dirIsNeg);
    }
    bool intersect(const Ray &ray, float &tnear, uint32_t &index) const {
        std::cout << "intersect 2\n";
        std::array<int, 3> dirIsNeg;
        return bounds.IntersectP(ray, ray.direction_inv, dirIsNeg);
    }
    Intersection getIntersection(Ray ray) {
        // std::cout << "getIntersection\n";
        Intersection inter;

        std::array<float, 3> pMin = {x - 0.0001f, fmin(y0, y1), fmin(z0, z1)};
        std::array<float, 3> pMax = {x + 0.0001f, fmax(y0, y1), fmax(z0, z1)};
        // auto pMax = Vector3f(x, fmax(y0, y1), fmax(z0, z1));

        float t0 = 0, t1 = ray.t_max;
        
        float invRayX = ray.direction_inv.x;
        float tNear = (bounds.pMin.x - ray.origin.x) * invRayX;
        float tFar = (bounds.pMax.x - ray.origin.x) * invRayX;
        if (tNear > tFar)
            std::swap(tNear, tFar);
        t0 = tNear > t0 ? tNear : t0;
        t1 = tFar < t1 ? tFar : t1;
        if (t0 > t1)
            return inter;
        float invRayY = ray.direction_inv.y;
        tNear = (bounds.pMin.y - ray.origin.y) * invRayY;
        tFar = (bounds.pMax.y - ray.origin.y) * invRayY;
        if (tNear > tFar)
            std::swap(tNear, tFar);
        t0 = tNear > t0 ? tNear : t0;
        t1 = tFar < t1 ? tFar : t1;
        if (t0 > t1)
            return inter;
        float invRayZ = ray.direction_inv.z;
        tNear = (bounds.pMin.z - ray.origin.z) * invRayZ;
        tFar = (bounds.pMax.z - ray.origin.z) * invRayZ;
        if (tNear > tFar)
            std::swap(tNear, tFar);
        t0 = tNear > t0 ? tNear : t0;
        t1 = tFar < t1 ? tFar : t1;
        if (t0 > t1)
            return inter;

        // for (int i = 0; i < 3; i++) {
        //     float invRay = ray.direction_inv[i];
        //     float tNear = (pMin[i] - ray.origin[i]) * invRay;
        //     float tFar = (pMax[i] - ray.origin[i]) * invRay;
        //     if (tNear > tFar)
        //         std::swap(tNear, tFar);
        //     t0 = tNear > t0 ? tNear : t0;
        //     t1 = tFar < t1 ? tFar : t1;
        //     if (t0 > t1)
        //         return inter;
        // }

        inter.obj = dynamic_cast<Object*>(this);
        inter.m = this->m;
        inter.happened = true;
        inter.normal = Vector3f(0, 0, 1);
        inter.coords = t0 * ray.direction + ray.origin;
        inter.distance = t0;

        return inter;
    }
    void getSurfaceProperties(const Vector3f &P, const Vector3f &I, const uint32_t &index, const Vector2f &uv, Vector3f &N, Vector2f &st) const {
        // std::cout << "getSurfaceProperties\n";
        // N = Vector3f(0, 1, 0);
		N = P.x - x > 0 ? Vector3f(1, 0, 0) : Vector3f(-1, 0, 0);
        // st = Vector2f(0, 1);
    }
    Vector3f evalDiffuseColor(const Vector2f &st) const {
        return m->getColor();
    }
    Bounds3 getBounds() {return bounds;}
};