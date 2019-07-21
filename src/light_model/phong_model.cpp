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
            vec3f point = ray.pointAtParam(closestHit.t);
            vec3f normal = closestHit.entity->normalAtPoint(point);
            for(Light* light : lights) {
                vec3f v = (ray.origin - point).normalize();
                vec3f l = (light->position - point).normalize();
                vec3f h = (v + l) / (v + l).magnitude();

                Color diffuse = closestHit.entity->getDiffuse() *
                    light->intensity *
                    fmax(0, vec3f::dot(normal, l));
                Color specular = closestHit.entity->getSpecular() *
                    light->intensity *
                    std::pow(fmax(0, vec3f::dot(normal, h)), closestHit.entity->getShininess());

                color += diffuse + specular;
            }
        }
        return color;
    }
}
