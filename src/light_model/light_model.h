#ifndef __LIGHT_MODEL_H_
#define __LIGHT_MODEL_H_

#include <vector>

#include <color.h>
#include <light.h>
#include <entity.h>


namespace raytracer {
    class LightModel {
        public:
            LightModel() {}

            virtual Color traceRay(const Ray& ray,
                                   const std::vector<Entity*>& scene,
                                   const std::vector<Light*>& lights) const = 0;
    };

    class PhongModel : public LightModel {
        public:
            PhongModel() : _ambient(Color(0.1, 0.1, 0.1)) {}
            Color traceRay(const Ray& ray,
                           const std::vector<Entity*>& scene,
                           const std::vector<Light*>& lights) const override;

        private:
            Color _ambient;

    };
};


#endif // __LIGHT_MODEL_H_
