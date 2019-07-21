#include <entity.h>

#include <cmath>

#include <iostream>
namespace raytracer {
    Plane::Plane(const Transform& transform, const Material& material) : Entity(transform, material) {
    }

    bool Plane::rayIntersects(const Ray& ray) const {
        vec3f normal = getNormal();

        float denom = vec3f::dot(normal, ray.direction);

        if(fabs(denom) > EPSILON) {
            float t = vec3f::dot(transform.getPosition() - ray.origin, normal) / denom;
            return t >= EPSILON;
        }

        return false;

    }

    bool Plane::rayIntersects(const Ray& ray, RayHit& hit) const {
        vec3f normal = getNormal();

        float denom = vec3f::dot(normal, ray.direction);

        if(fabs(denom) > Entity::_eps) {
            float t = vec3f::dot(transform.getPosition() - ray.origin, normal) / denom;
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

    vec3f Plane::getNormal() const {
        return transform.getRotationMatrix() * vec3f(0, 1, 0);
    }

    vec3f Plane::normalAtPoint(const vec3f& point) const {
        return getNormal();
    }
}
