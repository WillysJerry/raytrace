#ifndef __LIGHT_MODEL_H_
#define __LIGHT_MODEL_H_

#include <vector>

#include <color.h>
#include <light.h>
#include <entity.h>
#include <ray_hit.h>


namespace raytracer {
    class LightModel {
        public:
            LightModel() {}

            virtual Color traceRay(const Ray& ray,
                                   const std::vector<Entity*>& scene,
                                   const std::vector<Light*>& lights) const;

        protected:
            virtual Color processRayHit(const Ray& ray,
                                        const RayHit& hit,
                                        const std::vector<Entity*>& scene,
                                        const std::vector<Light*>& lights) const = 0;
    };

    class LambertModel : public LightModel {
        public:
            LambertModel() : _ambient(Color(0.01, 0.01, 0.01)) {}

            virtual Color processRayHit(const Ray& ray,
                                        const RayHit& hit,
                                        const std::vector<Entity*>& scene,
                                        const std::vector<Light*>& lights) const override;

        protected:
            Color _ambient;

            virtual Color calculateDiffuseComponent(const Entity& entity,
                                                    const Light& light,
                                                    const vec3f& normal,
                                                    const vec3f& lightVector) const;
    };

    class PhongModel : public LambertModel {
        public:
            virtual Color processRayHit(const Ray& ray,
                                        const RayHit& hit,
                                        const std::vector<Entity*>& scene,
                                        const std::vector<Light*>& lights) const override;

        protected:
            virtual Color calculateSpecularComponent(const Entity& entity,
                                                     const Light& light,
                                                     const vec3f& normal,
                                                     const vec3f& halfVector) const;
    };
};


#endif // __LIGHT_MODEL_H_
