#include "camera.h"

#include <ray.h>
#include <ray_hit.h>

namespace raytracer {

    Camera::Camera(const int& px, const int& py, const float& focalDist, const vec3f& position)
        : _px(px), _py(py), _focalDist(focalDist) {

        transform.translate(position);
        //transform.setPosition(position);
        _l = -1.0; _r =  1.0;
        _t =  1.0; _b = -1.0;
    }

    Camera::~Camera() {
    }

    vec3f Camera::getGazeDirection() const {
        return transform.getForwardVector();
    }

    void Camera::render(const LightModel& lightModel, const std::vector<Entity*>& scene, const std::vector<Light*>& lights, PixBuf*& pixelBuffer) const {
        pixelBuffer = new PixBuf(_px, _py);
        for(int i = 0; i < _px; i++) {
            for(int j = 0; j < _py; j++) {
                vec3f pixelPos = getPixelPosition(i, j);
                vec3f dir = pixelPos + getGazeDirection();

                Ray ray(transform.getPosition(),
                        dir.normalize());

                (*pixelBuffer)(i, j) = lightModel.traceRay(ray, scene, lights);
            }
        }
    }

    vec3f Camera::getPixelPosition(const int& x, const int& y) const {
        return vec3f(_l + (_r - _l)*(x + 0.5)/_px,
                     _b + (_t - _b)*(y + 0.5)/_py,
                     0.0);
    }
};
