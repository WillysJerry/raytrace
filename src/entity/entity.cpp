#include <entity.h>

namespace raytracer {
    const float Entity::_eps = 0.0001;

    Entity::Entity(const Transform& transform, const Material& material) : transform(transform), _material(material) {
    }
}
