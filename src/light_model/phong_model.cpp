#include <light_model.h>

#include <cmath>

namespace raytracer {

    Color PhongModel::processRayHit(const Ray& ray,
                                    const RayHit& hit,
                                    const std::vector<Entity*>& scene,
                                    const std::vector<Light*>& lights) const {
        vec3f color = _ambient;
        vec3f point = ray.pointAtParam(hit.t);
        vec3f normal = hit.entity->normalAtPoint(point);

        for(Light* light : lights) {
            vec3f v = (ray.origin - point).normalize();
            vec3f l = (light->position - point).normalize();
            vec3f h = (v + l) / (v + l).magnitude();

            Color diffuse = calculateDiffuseComponent(*hit.entity,
                                                      *light,
                                                      normal,
                                                      l);

            Color specular = calculateSpecularComponent(*hit.entity,
                                                        *light,
                                                        normal,
                                                        l);

            color += diffuse + specular;
        }

        return color;
    }

    Color PhongModel::calculateSpecularComponent(const Entity& entity,
                                                const Light& light,
                                                const vec3f& normal,
                                                const vec3f& halfVector) const {

        return entity.getSpecular() *
            light.intensity *
            std::pow(fmax(0, vec3f::dot(normal, halfVector)), entity.getShininess());
    }
}
