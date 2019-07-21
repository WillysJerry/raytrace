#include <light_model.h>

#include <cmath>

namespace raytracer {

    Color LambertModel::processRayHit(const Ray& ray,
                                    const RayHit& hit,
                                    const std::vector<Entity*>& scene,
                                    const std::vector<Light*>& lights) const {
        vec3f color = _ambient;
        vec3f point = ray.pointAtParam(hit.t);
        vec3f normal = hit.entity->normalAtPoint(point);

        for(Light* light : lights) {
            vec3f l = (light->position - point).normalize();

            Color diffuse = calculateDiffuseComponent(*hit.entity,
                                                      *light,
                                                      normal,
                                                      l);

            color += diffuse;
        }

        return color;
    }

    Color LambertModel::calculateDiffuseComponent(const Entity& entity,
                                                  const Light& light,
                                                  const vec3f& normal,
                                                  const vec3f& lightVector) const {

        return  entity.getDiffuse() *
                light.intensity *
                fmax(0, vec3f::dot(normal, lightVector));
    }
}
