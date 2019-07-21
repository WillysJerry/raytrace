#include "light_model.h"

#include <cmath>
#include <limits>

namespace raytracer {

    Color PhongModel::traceRay(const Ray& ray,
                               const std::vector<Entity*>& scene,
                               const std::vector<Light*>& lights) const {



        Color color = _ambient;

        bool hitSomething = false;
        float closest = std::numeric_limits<float>::max();
        RayHit closestHit;
        Entity* closestEntity;

        RayHit hit;
        for(Entity* entity : scene) {
            if(entity->rayIntersects(ray, hit)) {
                if(hit.t <= closest) {
                    hitSomething = true;
                    closest = hit.t;
                    closestHit = hit;
                    closestEntity = entity;
                }

            }
        }

        if(hitSomething) {
            for(Light* light : lights) {
                vec3f v = (ray.origin - closestHit.point).normalize();
                vec3f l = (light->position - closestHit.point).normalize();
                vec3f h = (v + l) / (v + l).magnitude();

                Color diffuse = closestEntity->getDiffuse() *
                    light->intensity *
                    fmax(0, vec3f::dot(closestHit.normal, l));
                Color specular = closestEntity->getSpecular() *
                    light->intensity *
                    std::pow(fmax(0, vec3f::dot(closestHit.normal, h)), closestEntity->getShininess());

                color += diffuse + specular;
            }
        }
        return color;
    }
}
