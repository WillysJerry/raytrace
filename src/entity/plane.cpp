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

    bool Plane::rayIntersects(const Ray& ray) const {
        float denom = vec3f::dot(_normal, ray.direction);

        if(fabs(denom) > EPSILON) {
            float t = vec3f::dot(transform.getPosition() - ray.origin, _normal) / denom;
            return t >= EPSILON;
        }

        return false;

    }

    bool Plane::rayIntersects(const Ray& ray, RayHit& hit) const {
        float denom = vec3f::dot(_normal, ray.direction);

        if(fabs(denom) > Entity::_eps) {
            float t = vec3f::dot(transform.getPosition() - ray.origin, _normal) / denom;
            if (t >= EPSILON) {

                hit.t = t;
                hit.entity = this;
                //hit.point = ray.origin + ray.direction * t;
                //hit.normal = _normal;
                return true;
            }
        }

        return false;
    }

    vec3f Plane::normalAtPoint(const vec3f& point) const {
        return _normal;
    }
}
