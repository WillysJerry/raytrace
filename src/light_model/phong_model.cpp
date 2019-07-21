#include <light_model.h>

#include <cmath>

namespace raytracer {

    Color PhongModel::calculateLightContribution(const Ray& fromRay,
                                                 const Light& light,
                                                 const Entity& entity,
                                                 const vec3f& hitPoint,
                                                 const vec3f& normal,
                                                 const vec3f& toLight) const {

        vec3f view = (fromRay.origin - hitPoint).normalize();
        vec3f half = (view + toLight) / (view + toLight).magnitude();

        Color diffuse = calculateDiffuseComponent(entity,
                                                  light,
                                                  normal,
                                                  toLight);

        Color specular = calculateSpecularComponent(entity,
                                                    light,
                                                    normal,
                                                    half);
        return diffuse + specular;
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
