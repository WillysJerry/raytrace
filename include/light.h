#ifndef __LIGHT_H_
#define __LIGHT_H_

#include <math3d.h>
#include <color.h>

namespace raytracer {
    class Light {
        public:
            vec3f position;
            Color color;
            float intensity;

            Light(vec3f position,
                  Color color = Color(1.0, 1.0, 1.0),
                  float intensity = 1.0) :
                position(position), color(color), intensity(intensity) {}

    };
};

#endif // __LIGHT_H_
