#include <light_model.h>

#include <limits>

namespace raytracer {
    Color LightModel::traceRay(const Ray& ray,
                               const std::vector<Entity*>& scene,
                               const std::vector<Light*>& lights) const {
        RayHit closestHit;
        if(getClosestRayHit(ray, scene, closestHit)) {
            return fireLightRays(ray, closestHit, scene, lights);
            //return processRayHit(ray, closestHit, scene, lights);
        }

        return Color(0, 0, 0);
    }

    Color LightModel::fireLightRays(const Ray& fromRay,
                                    const RayHit& hitPoint,
                                    const std::vector<Entity*>& scene,
                                    const std::vector<Light*>& lights) const {

        vec3f point = fromRay.pointAtParam(hitPoint.t);
        vec3f normal = hitPoint.entity->normalAtPoint(point);

        Color color(0,0,0);

        for(Light* light : lights) {
            vec3f l = (light->position - point).normalize();

            // Is point in shadow?
            Ray shadowRay = createReflectionRay(point, l);
            RayHit shadowHit;
            if(! (getClosestRayHit(shadowRay, scene, shadowHit) && shadowHit.t < vec3f::distance(shadowRay.origin, light->position)) ) {

                color += calculateLightContribution(fromRay,
                                                    *light,
                                                    *hitPoint.entity,
                                                    point,
                                                    normal,
                                                    l);

            }

        }

        return color;
    }

    bool LightModel::checkRayHit(const Ray& ray, const std::vector<Entity*>& scene) const {
        for(Entity* entity : scene) {
            if(entity->rayIntersects(ray))
                return true;
        }

        return false;
    }

    bool LightModel::getClosestRayHit(const Ray& ray,
                                    const std::vector<Entity*>& scene,
                                    RayHit& closestHit) const {
        bool hitSomething = false;
        closestHit.t = std::numeric_limits<float>::max();
        closestHit.entity = NULL;

        RayHit hit;
        for(Entity* entity : scene) {
            if(entity->rayIntersects(ray, hit)) {
                if(hit.t <= closestHit.t) {
                    hitSomething = true;
                    closestHit = hit;
                }

            }
        }

        return hitSomething;
    }

    Ray LightModel::createReflectionRay(const vec3f& position, const vec3f& direction) const {
        Ray r(position, direction);
        r.marchOriginForward();
        return r;
    }

};
