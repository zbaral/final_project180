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
    Box(const Vector3f p1, Vector3f p2, float y_rot) : y_rotation(y_rot), m(new Material()) {
        b = Bounds3(p1, p2);
	}
	Vector3f rotatePoint(const Vector3f v, float rot) const {
		Vector3f center = (b.pMin + b.pMax) / 2.;
        Vector3f vec = v - center;
		float angle = rot * M_PI / 180.;
        vec.x = vec.x * std::cos(angle) + vec.z * std::sin(angle);
        vec.z = -vec.x * std::sin(angle) + vec.z * std::cos(angle);
        vec += center;
        return vec;
	}
	Vector3f rotateVector(const Vector3f v, float rot) const {
        Vector3f vec = v;
		float angle = rot * M_PI / 180.;
        vec.x = vec.x * std::cos(angle) + vec.z * std::sin(angle);
        vec.z = -vec.x * std::sin(angle) + vec.z * std::cos(angle);
        return vec;
	}
	Ray rotateRay(const Ray& ray) const {
		Vector3f orig = rotatePoint(ray.origin, y_rotation);
		Vector3f dir = rotateVector(ray.direction, y_rotation);
		dir = normalize(dir);
		Ray r(orig, dir);
		r.t_min = ray.t_min;
		r.t_max = ray.t_max;
		return r;
	}
    bool intersect(const Ray& ray) {
        Ray r = rotateRay(ray);
        std::array<int, 3> dirIsNeg;
        return b.IntersectP(r, r.direction_inv, dirIsNeg);
    }
    bool intersect(const Ray &ray, float &tnear, uint32_t &index) const {
		Ray r = rotateRay(ray);
        std::array<int, 3> dirIsNeg;
        return b.IntersectP(r, r.direction_inv, dirIsNeg);
    }
	Intersection getIntersection(Ray ray) {
        Intersection inter;
        Ray r = rotateRay(ray);

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

		if(tMin < 0) return inter;

        Vector3f point = r.origin + tMin * r.direction;
        Vector3f normal;
        if(abs(point.x - b.pMin.x) < ZETA) normal = Vector3f(-1,0,0);
        else if(abs(point.x - b.pMax.x) < ZETA) normal = Vector3f(1,0,0);
        else if(abs(point.y - b.pMin.y) < ZETA) normal = Vector3f(0,-1,0);
        else if(abs(point.y - b.pMax.y) < ZETA) normal = Vector3f(0,1,0);
        else if(abs(point.z - b.pMin.z) < ZETA) normal = Vector3f(0,0,-1);
        else if(abs(point.z - b.pMax.z) < ZETA) normal = Vector3f(0,0,1);

		point = rotatePoint(point, -y_rotation);
		normal = normalize(rotateVector(normal, -y_rotation));

        Vector3f diff = point - r.origin;
		float dist = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

        inter.obj = dynamic_cast<Object*>(this);
        inter.m = this->m;
        inter.happened = true;
        inter.normal = normal;
        inter.coords = point + normal;
        inter.distance = dist;

        return inter;
    }
	void getSurfaceProperties(const Vector3f &P, const Vector3f &I, const uint32_t &index, const Vector2f &uv, Vector3f &N, Vector2f &st) const {
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
    Bounds3 getBounds() {
		Vector3f p1 = b.pMin;
		Vector3f p2 = Vector3f(b.pMin.x, b.pMin.y, b.pMax.z);
		Vector3f p3 = Vector3f(b.pMin.x, b.pMax.y, b.pMin.z);
		Vector3f p4 = Vector3f(b.pMin.x, b.pMax.y, b.pMax.z);
		Vector3f p5 = Vector3f(b.pMax.x, b.pMin.y, b.pMin.z);
		Vector3f p6 = Vector3f(b.pMax.x, b.pMin.y, b.pMax.z);
		Vector3f p7 = Vector3f(b.pMax.x, b.pMax.y, b.pMin.z);
		Vector3f p8 = b.pMax * 100;
		Bounds3 b1 = Bounds3(rotatePoint(p1, y_rotation), rotatePoint(p8, y_rotation));
		Bounds3 b2 = Bounds3(rotatePoint(p2, y_rotation), rotatePoint(p7, y_rotation));
		Bounds3 b3 = Bounds3(rotatePoint(p3, y_rotation), rotatePoint(p6, y_rotation));
		Bounds3 b4 = Bounds3(rotatePoint(p4, y_rotation), rotatePoint(p5, y_rotation));
		std::cout << "old pMin: " << b.pMin << '\n';
		std::cout << "old pMax: " << b.pMax << '\n';
		std::cout << "new pMin: " << Union(Union(b1, b2), Union(b3, b4)).pMin << '\n';
		std::cout << "new pMax: " << Union(Union(b1, b2), Union(b3, b4)).pMax << "\n\n";
		return Union(Union(b1, b2), Union(b3, b4));
	}
};