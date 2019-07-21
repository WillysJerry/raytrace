#ifndef __RAY_H_
#define __RAY_H_

#include <math3d.h>

namespace raytracer {
    class Ray {
        public:
            vec3f origin;
            vec3f direction;

            Ray(vec3f origin, vec3f direction) : origin(origin),
                                                 direction(direction) {}
    };
};


#endif // __RAY_H_
