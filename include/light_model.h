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
            LightModel() : _ambient(Color(0.01, 0.01, 0.01)) {}

            virtual Color traceRay(const Ray& ray,
                                   const std::vector<Entity*>& scene,
                                   const std::vector<Light*>& lights) const;

        protected:
            Color _ambient;

            virtual Color fireLightRays(const Ray& fromRay,
                                        const RayHit& hitPoint,
                                        const std::vector<Entity*>& scene,
                                        const std::vector<Light*>& lights) const;

            virtual bool checkRayHit(const Ray& ray,
                                     const std::vector<Entity*>& scene) const;

            virtual bool getClosestRayHit(const Ray& ray,
                                          const std::vector<Entity*>& scene,
                                          RayHit& closestHit) const;

            virtual Color calculateLightContribution(const Ray& fromRay,
                                                     const Light& light,
                                                     const Entity& entity,
                                                     const vec3f& hitPoint,
                                                     const vec3f& normal,
                                                     const vec3f& toLight) const = 0;

            Ray createReflectionRay(const vec3f& position, const vec3f& direction) const;
    };

    class LambertModel : public LightModel {
        public:

        protected:
            virtual Color calculateLightContribution(const Ray& fromRay,
                                                     const Light& light,
                                                     const Entity& entity,
                                                     const vec3f& hitPoint,
                                                     const vec3f& normal,
                                                     const vec3f& toLight) const override;

            virtual Color calculateDiffuseComponent(const Entity& entity,
                                                    const Light& light,
                                                    const vec3f& normal,
                                                    const vec3f& lightVector) const;
    };

    class PhongModel : public LambertModel {
        public:

        protected:
            virtual Color calculateLightContribution(const Ray& fromRay,
                                                     const Light& light,
                                                     const Entity& entity,
                                                     const vec3f& hitPoint,
                                                     const vec3f& normal,
                                                     const vec3f& toLight) const override;

            virtual Color calculateSpecularComponent(const Entity& entity,
                                                     const Light& light,
                                                     const vec3f& normal,
                                                     const vec3f& halfVector) const;
    };
};


#endif // __LIGHT_MODEL_H_
