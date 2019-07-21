#ifndef __MATERIAL_H_
#define __MATERIAL_H_

#include <math3d.h>
#include <color.h>

namespace raytracer {
    struct Material {
        public:
            Color diffuse;
            Color specular;

            float shininess;

            Material(const Color& diffuse = Color(1, 1, 1),
                     const Color& specular = Color(0, 0, 0),
                     const float& shininess = 0.0) :
                diffuse(diffuse), specular(specular), shininess(shininess) {}
    };
};


#endif // __MATERIAL_H_
