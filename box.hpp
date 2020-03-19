#include "Object.hpp"
#include "Vector.hpp"
#include "Bounds3.hpp"
#include "Material.hpp"
#include "Rect.hpp"
#include <math.h>

class box : public Object {
public:
    Bounds3 b;
    Material *m;
    float y_rotation;
    box() {}
    box(const Vector3f p1, Vector3f p2, float y_rot) 
    : y_rotation(y_rot), m(new Material()){
        b = Bounds3(p1, p2);
    }

    Ray rotateRay(const Ray& ray){
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

    bool intersect(const Ray& ray) {
        Ray r = rotateRay(ray);
        std::array<int, 3> dirIsNeg;
        return b.IntersectP(r, r.direction_inv, dirIsNeg);
    }
    bool intersect(const Ray& ray, float &, uint32_t &) {
        return intersect(ray);
    }
    Intersection getIntersection(Ray _ray) {
        Intersection inter;
        Ray r = rotateRay(_ray);

		float t = (z - r.origin.z) / r.direction.z;
		if (t < 0)
			return inter;
		Vector3f point = r.origin + t * r.direction;
		if (point.x < x0 || point.x > x1 || point.y < y0 || point.y > y1)
			return inter;

		Vector3f diff = point - r.origin;
		float dist = sqrtf(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

		Vector3f normal = r.origin.z - z > 0 ? Vector3f(0, 0, 1) : Vector3f(0, 0, -1);

        inter.obj = dynamic_cast<Object*>(this);
        inter.m = this->m;
        inter.happened = true;
        inter.normal = normal;
        inter.coords = point + normal * Vector3f(0, 0, 0.001f);
        inter.distance = dist;

        return inter;
    }
    void getSurfaceProperties(const Vector3f &, const Vector3f &, const uint32_t &, const Vector2f &, Vector3f &, Vector2f &){

    }
    Vector3f evalDiffuseColor(const Vector2f &) {
        return m->getColor();
    }
    Bounds3 getBounds() {return b;}

};