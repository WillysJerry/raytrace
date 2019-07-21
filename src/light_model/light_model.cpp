#include "light_model.h"

#include <limits>

namespace raytracer {
    Color LightModel::traceRay(const Ray& ray,
                               const std::vector<Entity*>& scene,
                               const std::vector<Light*>& lights) const {

        bool hitSomething = false;
        RayHit closestHit(std::numeric_limits<float>::max(), NULL);

        RayHit hit;
        for(Entity* entity : scene) {
            if(entity->rayIntersects(ray, hit)) {
                if(hit.t <= closestHit.t) {
                    hitSomething = true;
                    closestHit = hit;
                }

            }
        }

        if(hitSomething) {
            return processRayHit(ray, closestHit, scene, lights);
        }

        return Color(0, 0, 0);
    }

};
