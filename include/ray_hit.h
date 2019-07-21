#ifndef __RAY_HIT_H_
#define __RAY_HIT_H_

#include <math3d.h>
#include <entity.h>

namespace raytracer {
    struct RayHit {
        public:
            float t;
            vec3f point;
            vec3f normal;

            RayHit() {}
            /*RayHit(const vec3f& point, const vec3f& normal)
                : point(point), normal(normal) {}*/

            RayHit(const float& t, const vec3f& point, const vec3f& normal)
                : t(t), point(point), normal(normal) {}
    };
};

#endif // __RAY_HIT_H_
