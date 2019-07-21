#include <entity.h>

#include <math3d.h>
#include <cmath>

namespace raytracer {
    Sphere::Sphere(const vec3f& position, const float& radius) :
        Entity(position), _radius(radius) {
    }

    Sphere::Sphere(const vec3f& position, const float& radius, const Material& material) :
        Entity(position, material), _radius(radius) {
    }

    bool Sphere::rayIntersects(const Ray& ray, RayHit& hit) const {
        vec3f to = ray.origin - transform.getPosition();

        float d0 = vec3f::dot(ray.direction, to);
        float denom = vec3f::dot(ray.direction, ray.direction);

        float disc = d0*d0 -
            denom *
            (vec3f::dot(to, to) - _radius*_radius);

        if(disc > Entity::_eps) {
            float sqrdDisc = sqrt(disc);
            float t0 = (vec3f::dot(-ray.direction, to) + sqrdDisc) / denom;
            float t1 = (vec3f::dot(-ray.direction, to) - sqrdDisc) / denom;

            float t = fmin(t0, t1);

            if(t < 0.0) {
                return false;
            }
            vec3f point = ray.origin + ray.direction * t;
            vec3f normal = (point - transform.getPosition()) / _radius;

            hit = RayHit(t, point, normal);
            return true;
        }
        return false;
    }
};
