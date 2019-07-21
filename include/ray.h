#ifndef __RAY_H_
#define __RAY_H_

#include <math3d.h>

namespace raytracer {
    class Ray {
        public:
            vec3f origin;
            vec3f direction;

            Ray(const vec3f& origin, const vec3f& direction) : origin(origin),
                                                               direction(direction) {}

            void marchOriginForward() { origin = origin + direction * EPSILON; }

            vec3f pointAtParam(const float& t) const { return origin + t * direction; }

    };
};


#endif // __RAY_H_
