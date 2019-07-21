#include <entity.h>

namespace raytracer {
    const float Entity::_eps = 0.0001;

    Entity::Entity(const vec3f& position) {
        transform.translate(position);
    }
    Entity::Entity(const vec3f& position, const Material& material) : _material(material) {
        transform.translate(position);
    }
}
