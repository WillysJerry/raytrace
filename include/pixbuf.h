#ifndef __PIXBUF_H_
#define __PIXBUF_H_

#include <color.h>

namespace raytracer {
    class PixBuf {
        public:
            PixBuf(int w, int h) : _w(w), _h(h) {
                _pixels = new Color[w * h];
            }
            ~PixBuf() {
                delete[] _pixels;
            }

            int getWidth()  { return _w; }
            int getHeight() { return _h; }

            Color& operator()(size_t x, size_t y) {
                return _pixels[ x + y * _w];
            }
            const Color& operator()(size_t x, size_t y) const {
                return _pixels[ x + y * _w];
            }

        private:
            int _w, _h;
            Color* _pixels;
    };
}

#endif // __PIXBUF_H_
