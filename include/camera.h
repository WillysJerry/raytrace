#ifndef __CAMERA_H_
#define __CAMERA_H_

#include <vector>

#include <math3d.h>
#include <transform.h>
#include <pixbuf.h>
#include <entity.h>
#include <light_model.h>

namespace raytracer {
    class Camera {
        public:
            Transform transform;

            Camera(const int& px, const int& py, const float& focalDist, const vec3f& position = vec3f(0,0,0));
            ~Camera();

            void render(const LightModel& lightModel, const std::vector<Entity*>& scene, const std::vector<Light*>& lights, PixBuf*& pixelBuffer) const;

        private:

            int _px;
            int _py;
            float _focalDist;

            float _l, _r;
            float _t, _b;

            vec3f getPixelPosition(const int& x, const int& y) const;
    };

};

#endif // __CAMERA_H_
