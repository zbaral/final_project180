//
// Created by Göksu Güvendiren on 2019-05-14.
//

#pragma once

#include "Vector.hpp"
#include "Light.hpp"
#include "global.hpp"

class AreaLight : public Light
{
public:
    AreaLight(const Vector3f &p, const Vector3f &i, const float w, const float h) : Light(p, i), x(w), z(h)
    {
		// XZ Area Light pointing in -Y direction
        normal = Vector3f(0, -1, 0);
        u = Vector3f(1, 0, 0);
        v = Vector3f(0, 0, 1);
    }

    Vector3f SamplePoint() const
    {
        auto random_u = get_random_float();
        auto random_v = get_random_float();
        return position + random_u * u * x + random_v * v * z;
    }

    float x, z;
    Vector3f normal;
    Vector3f u;
    Vector3f v;
};
