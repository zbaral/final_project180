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
            bounds = Bounds3(Vector3f(x0, y0, z), Vector3f(x1, y1, z));
        }
    bool intersect(const Ray &ray) {
        std::array<int, 3> dirIsNeg;
        return bounds.IntersectP(ray, ray.direction_inv, dirIsNeg);
    }
    bool intersect(const Ray &ray, float &tnear, uint32_t &index) const {
        std::array<int, 3> dirIsNeg;
        return bounds.IntersectP(ray, ray.direction_inv, dirIsNeg);
    }
    Intersection getIntersection(Ray ray) {
        Intersection inter;

		float t = (z - ray.origin.z) / ray.direction.z;
		if (t < 0)
			return inter;
		Vector3f point = ray.origin + t * ray.direction;
		if (point.x < x0 || point.x > x1 || point.y < y0 || point.y > y1)
			return inter;

		Vector3f diff = point - ray.origin;
		float dist = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z + diff.z);

		Vector3f normal = ray.origin.z - z > 0 ? Vector3f(0, 0, 1) : Vector3f(0, 0, -1);

        inter.obj = dynamic_cast<Object*>(this);
        inter.m = this->m;
        inter.happened = true;
        inter.normal = normal;
        inter.coords = point + normal * Vector3f(0, 0, 0.001f);
        inter.distance = dist;

        return inter;
    }
    void getSurfaceProperties(const Vector3f &P, const Vector3f &I, const uint32_t &index, const Vector2f &uv, Vector3f &N, Vector2f &st) const {
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
            bounds = Bounds3(Vector3f(x0, y, z0), Vector3f(x1, y, z1));
        }
    bool intersect(const Ray &ray) {
        std::array<int, 3> dirIsNeg;
        return bounds.IntersectP(ray, ray.direction_inv, dirIsNeg);
    }
    bool intersect(const Ray &ray, float &tnear, uint32_t &index) const {
        std::array<int, 3> dirIsNeg;
        return bounds.IntersectP(ray, ray.direction_inv, dirIsNeg);
    }
    Intersection getIntersection(Ray ray) {
        Intersection inter;

		float t = (y - ray.origin.y) / ray.direction.y;
		if (t < 0)
			return inter;
		Vector3f point = ray.origin + t * ray.direction;
		if (point.x < x0 || point.x > x1 || point.z < z0 || point.z > z1)
			return inter;

		Vector3f diff = point - ray.origin;
		float dist = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z + diff.z);

		Vector3f normal = ray.origin.y - y > 0 ? Vector3f(0, 1, 0) : Vector3f(0, -1, 0);

        inter.obj = dynamic_cast<Object*>(this);
        inter.m = this->m;
        inter.happened = true;
        inter.normal = normal;
        inter.coords = point + normal * Vector3f(0, 0.001f, 0);
        inter.distance = dist;

        return inter;
    }
    void getSurfaceProperties(const Vector3f &P, const Vector3f &I, const uint32_t &index, const Vector2f &uv, Vector3f &N, Vector2f &st) const {
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
            bounds = Bounds3(Vector3f(x, y0, z0), Vector3f(x, y1, z1));
        }
    bool intersect(const Ray &ray) {
        std::array<int, 3> dirIsNeg;
        return bounds.IntersectP(ray, ray.direction_inv, dirIsNeg);
    }
    bool intersect(const Ray &ray, float &tnear, uint32_t &index) const {
        std::array<int, 3> dirIsNeg;
        return bounds.IntersectP(ray, ray.direction_inv, dirIsNeg);
    }
    Intersection getIntersection(Ray ray) {
        Intersection inter;

		float t = (x - ray.origin.x) / ray.direction.x;
		if (t < 0)
			return inter;
		Vector3f point = ray.origin + t * ray.direction;
		if (point.y < y0 || point.y > y1 || point.z < z0 || point.z > z1)
			return inter;

		Vector3f diff = point - ray.origin;
		float dist = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z + diff.z);

		Vector3f normal = ray.origin.x - x > 0 ? Vector3f(1, 0, 0) : Vector3f(-1, 0, 0);

        inter.obj = dynamic_cast<Object*>(this);
        inter.m = this->m;
        inter.happened = true;
        inter.normal = normal;
        inter.coords = point + normal * Vector3f(0.001f, 0, 0);
        inter.distance = dist;

        return inter;
    }
    void getSurfaceProperties(const Vector3f &P, const Vector3f &I, const uint32_t &index, const Vector2f &uv, Vector3f &N, Vector2f &st) const {
		N = P.x - x > 0 ? Vector3f(1, 0, 0) : Vector3f(-1, 0, 0);
        // st = Vector2f(uv.x, 1 - uv.y);
    }
    Vector3f evalDiffuseColor(const Vector2f &st) const {
		return m->getColor();
    }
    Bounds3 getBounds() {return bounds;}
};