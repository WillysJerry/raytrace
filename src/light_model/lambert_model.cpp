#include <light_model.h>

#include <cmath>

namespace raytracer {

    Color LambertModel::calculateLightContribution(const Ray& fromRay,
                                                   const Light& light,
                                                   const Entity& entity,
                                                   const vec3f& hitPoint,
                                                   const vec3f& normal,
                                                   const vec3f& toLight) const {

        Color diffuse = calculateDiffuseComponent(entity,
                                                  light,
                                                  normal,
                                                  toLight);

        return diffuse;
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
