#ifndef __RAY_HIT_H_
#define __RAY_HIT_H_

#include <math3d.h>
#include <entity.h>

namespace raytracer {
    class Entity;

    struct RayHit {
        public:
            float t;
            const Entity* entity;

            RayHit() {}
            /*RayHit(const vec3f& point, const vec3f& normal)
                : point(point), normal(normal) {}*/

            RayHit(float t, const Entity* entity)
                : t(t), entity(entity) {}
    };
};

#endif // __RAY_HIT_H_
