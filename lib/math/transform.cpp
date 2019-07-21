#include <transform.h>

#include <cmath>

namespace raytracer {

    Transform::Transform() : _position(vec4f(0,0,0,1)) {
        _translationMatrix = mat4x4f::identity();
        _rotationMatrix = mat4x4f::identity();
        _scalingMatrix = mat4x4f::identity();

    }

    Transform::~Transform() {
    }

    vec3f Transform::getForwardVector() const {
        return (_rotationMatrix * vec4f(0, 0, 1, 1)).normalize();
    }

    vec3f Transform::getUpVector() const {
        return (_rotationMatrix * vec4f(0, 1, 0, 1)).normalize();
    }

    vec3f Transform::getRightVector() const {
        return (_rotationMatrix * vec4f(-1, 0, 0, 1)).normalize();
    }

    void Transform::translate(const vec3f& translation) {
        _translationMatrix = _translationMatrix * mkTranslationMatrix(translation);
        _position = _translationMatrix * vec4f();
    }

    void Transform::scale(const vec3f& scaling) {
        _scalingMatrix = _scalingMatrix * mkScalingMatrix(scaling);
    }

    void Transform::axisRotate(const float& angle, const Axis& axis) {
        _rotationMatrix = _rotationMatrix * mkRotationMatrix(angle, axis);
    }

    mat4x4f Transform::mkTranslationMatrix(const vec3f& translation) {
        mat4x4f ret = mat4x4f::identity();
        ret[ 3] = translation.x;
        ret[ 7] = translation.y;
        ret[11] = translation.z;
        return ret;
    }
    mat4x4f Transform::mkScalingMatrix(const vec3f& scaling) {
        mat4x4f ret = mat4x4f::identity();
        ret[ 0] = scaling.x;
        ret[ 5] = scaling.y;
        ret[10] = scaling.z;
        return ret;
    }
    mat4x4f Transform::mkRotationMatrix(const float& angle, const Axis& axis) {
        mat4x4f ret = mat4x4f::identity();
        switch(axis) {
            case X:
                ret[ 5] =  cos(angle); ret[ 6] = sin(angle);
                ret[ 9] = -sin(angle); ret[10] = cos(angle);
                break;
            case Y:
                ret[ 0] = cos(angle); ret[ 2] = -sin(angle);
                ret[ 8] = sin(angle); ret[10] =  cos(angle);
                break;
            case Z:
                ret[ 0] =  cos(angle); ret[ 1] = sin(angle);
                ret[ 4] = -sin(angle); ret[ 5] = cos(angle);
                break;
        }
        return ret;
    }

};
