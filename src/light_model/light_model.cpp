#include <light_model.h>

#include <limits>

namespace raytracer {
    Color LightModel::traceRay(const Ray& ray,
                               const std::vector<Entity*>& scene,
                               const std::vector<Light*>& lights) const {

        return vec3f::clamp01(_ambient + doRayTrace(ray, scene, lights, _mirrorRecursionDepth));
    }

    Color LightModel::doRayTrace(const Ray& ray,
                                 const std::vector<Entity*>& scene,
                                 const std::vector<Light*>& lights,
                                 int mirrorRecursions) const {

        Color color = Color(0, 0, 0);

        if(mirrorRecursions < 0)
            return color;

        RayHit closestHit;


        if(getClosestRayHit(ray, scene, closestHit)) {
            vec3f point = ray.pointAtParam(closestHit.t);
            vec3f normal = closestHit.entity->normalAtPoint(point);

            color += fireLightRays(ray, closestHit, scene, lights);

            Ray mirrorRay(point, vec3f::mirror(ray.direction, normal));
            mirrorRay.marchOriginForward();
            color += closestHit.entity->getReflectivity() * doRayTrace(mirrorRay, scene, lights, mirrorRecursions - 1);
            //return processRayHit(ray, closestHit, scene, lights);
        }

        return color;
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
