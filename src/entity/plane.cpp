#include <entity.h>

#include <cmath>

#include <iostream>
namespace raytracer {
    Plane::Plane(const vec3f& position) : Entity(position) {
        _normal = vec3f(0, 1, 0);
    }

    Plane::Plane(const vec3f& position, const Material& material) : Entity(position, material) {
        _normal = vec3f(0, 1, 0);
    }

    bool Plane::rayIntersects(const Ray& ray, RayHit& hit) const {
        float denom = vec3f::dot(_normal, ray.direction);

        if(fabs(denom) > Entity::_eps) {
            float t = vec3f::dot(transform.getPosition() - ray.origin, _normal) / denom;
            if (t >= Entity::_eps) {

                hit.t = t;
                hit.point = ray.origin + ray.direction * t;
                hit.normal = _normal;
                return true;
            }
        }

        return false;
    }
}
