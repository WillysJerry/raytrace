#ifndef __TRANSFORM_H_
#define __TRANSFORM_H_

#include <math3d.h>

namespace raytracer {

    enum Axis { X, Y, Z };
    class Transform {
        public:

            Transform();
            ~Transform();

            const mat4x4f& getTranslationMatrix() const { return _translationMatrix; }
            const mat4x4f& getRotationMatrix()    const { return _rotationMatrix; }
            const mat4x4f& getScalingMatrix()     const { return _scalingMatrix; }

            vec3f getPosition() const { return _position; }

            vec3f getForwardVector() const;
            vec3f getUpVector() const;
            vec3f getRightVector() const;

            void translate(const vec3f& translation);
            void scale    (const vec3f& scaling);

            void axisRotate(const float& angle, const Axis& axis);

            static mat4x4f mkTranslationMatrix(const vec3f& translation);
            static mat4x4f mkScalingMatrix(const vec3f& scaling);
            static mat4x4f mkRotationMatrix(const float& angle, const Axis& axis);

        private:
            mat4x4f _translationMatrix;
            mat4x4f _rotationMatrix;
            mat4x4f _scalingMatrix;
            vec4f _position;
            //vec4f _scale;
            //vec4f _rotation;

            //void applyTransform();
    };
};


#endif // __TRANSFORM_H_
