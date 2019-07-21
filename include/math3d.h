#ifndef __MATH3D_H_
#define __MATH3D_H_

#include <cmath>
#include <ostream>

#define R2D 57.2958
#define D2R 0.0174533

#define RADIANS_TO_DEGREES(X) ( (X) * R2D )
#define DEGREES_TO_RADIANS(X) ( (X) * D2R )

namespace raytracer {
    template<class T>
    class Vector3;
    template<class T>
    class Vector4;

    static const float EPSILON = 0.0001f;

    inline float fmax(const float& x, const float& y) {
        return x > y ? x : y;
    }
    inline float fmin(const float& x, const float& y) {
        return x < y ? x : y;
    }
    inline float clamp01(const float& x) {
        return x > 0.0 ? (x < 1.0 ? x : 1.0) : 0.0;
    }

    template<class T>
    class Vector3 {
        public:
            union { T x; T r; };
            union { T y; T g; };
            union { T z; T b; };

            Vector3() : x(0), y(0), z(0) {}
            Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

            T sqrMagnitude() const {
                return x*x + y*y + z*z;
            }

            T magnitude() const {
                return std::sqrt(sqrMagnitude());
            }

            Vector3<T> normalize() const {
                return normalized(*this);
            }

            static Vector3<T> normalized(const Vector3<T>& vector) {
                return vector / vector.magnitude();
            }

            static T dot(const Vector3<T> lhs,
                         const Vector3<T> rhs) {
                return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
            }

            static Vector3<T> cross(const Vector3<T> lhs,
                                    const Vector3<T> rhs) {
                return Vector3<T>( lhs.y*rhs.z-lhs.z*rhs.y,
                                   lhs.z*rhs.x-lhs.x*rhs.z,
                                   lhs.x*rhs.y-lhs.y*rhs.x);
            }

            static T distance(const Vector3<T> a,
                              const Vector3<T> b) {
                Vector3<T> ab = b - a;
                return ab.magnitude();
            }

            friend Vector3<T> operator*(const T lhs, Vector3<T> rhs) {
                rhs.x *= lhs;
                rhs.y *= lhs;
                rhs.z *= lhs;
                return rhs;
            }
            friend Vector3<T> operator*(Vector3<T> lhs, const T rhs) {
                return operator*(rhs, lhs);
            }

            friend Vector3<T> operator/(Vector3<T> lhs, const T rhs) {
                lhs.x /= rhs;
                lhs.y /= rhs;
                lhs.z /= rhs;
                return lhs;
            }

            Vector3<T> operator-() const {
                return Vector3<T>(-this->x, -this->y, -this->z);
            }

            friend Vector3<T> operator+(Vector3<T> lhs,
                                        const Vector3<T> rhs) {
                lhs.x += rhs.x;
                lhs.y += rhs.y;
                lhs.z += rhs.z;
                return lhs;
            }

            friend Vector3<T> operator-(Vector3<T> lhs,
                                        const Vector3<T> rhs) {
                lhs.x -= rhs.x;
                lhs.y -= rhs.y;
                lhs.z -= rhs.z;
                return lhs;
            }

            Vector3<T>& operator+=(const Vector3<T>& rhs) {
                x += rhs.x;
                y += rhs.y;
                z += rhs.z;
                return *this;
            }

            Vector3<T>& operator-=(const Vector3<T>& rhs) {
                x -= rhs.x;
                y -= rhs.y;
                z -= rhs.z;
                return *this;
            }

            operator Vector4<T>() const { return Vector4<T>(x, y, z, 1); }
    };

    typedef Vector3<float> vec3f;
    typedef Vector3<int>   vec3i;

    template<class T>
    class Vector4 {
        public:
            union { T x; T r; };
            union { T y; T g; };
            union { T z; T b; };
            union { T w; T a; };

            Vector4() : x(0), y(0), z(0), w(1) {}
            Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

            T sqrMagnitude() {
                return x*x + y*y + z*z + w*w;
            }

            T magnitude() {
                return std::sqrt(sqrMagnitude());
            }

            Vector4<T> normalize() {
                T len = magnitude();
                return Vector4<T>(x/len, y/len, z/len, w/len);
            }

            Vector3<T> homogenize() {
                // TODO: exception when w == 0?
                return Vector3<T>(x/w, y/w, z/w);
            }

            static T dot(const Vector4<T> lhs,
                         const Vector4<T> rhs) {
                return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z + lhs.w*rhs.w;
            }

            friend Vector4<T> operator*(const T lhs, Vector4<T> rhs) {
                rhs.x *= lhs;
                rhs.y *= lhs;
                rhs.z *= lhs;
                rhs.w *= lhs;
                return rhs;
            }
            friend Vector4<T> operator*(Vector4<T> lhs, const T rhs) {
                return operator*(rhs, lhs);
            }

            friend Vector4<T> operator/(Vector4<T> lhs, const T rhs) {
                lhs.x /= rhs;
                lhs.y /= rhs;
                lhs.z /= rhs;
                lhs.w /= rhs;
                return lhs;
            }

            friend Vector4<T> operator+(Vector4<T> lhs,
                                        const Vector4<T> rhs) {
                lhs.x += rhs.x;
                lhs.y += rhs.y;
                lhs.z += rhs.z;
                lhs.w += rhs.w;
                return lhs;
            }

            friend Vector4<T> operator-(Vector4<T> lhs,
                                        const Vector4<T> rhs) {
                lhs.x -= rhs.x;
                lhs.y -= rhs.y;
                lhs.z -= rhs.z;
                lhs.w -= rhs.w;
                return lhs;
            }

            Vector4<T>& operator+=(const Vector4<T>& rhs) {
                x += rhs.x;
                y += rhs.y;
                z += rhs.z;
                w += rhs.w;
                return *this;
            }

            Vector4<T>& operator-=(const Vector4<T>& rhs) {
                x -= rhs.x;
                y -= rhs.y;
                z -= rhs.z;
                w -= rhs.w;
                return *this;
            }

            operator Vector3<T>() const { return Vector3<T>(x, y, z); }
    };

    typedef Vector4<float> vec4f;
    typedef Vector4<int>   vec4i;

    template<class T>
    class Mat4x4 {
        public:
            T m[16];

            Mat4x4() {}
            Mat4x4(const T arr[16]) {for(int i=0;i<16;i++)m[i]=arr[i];}
            Mat4x4(const Mat4x4<T>& mat) {for(int i=0;i<16;i++)m[i]=mat.m[i];}

            Mat4x4<T> transpose() const {
                Mat4x4<T> res;
                for(int i = 0; i < 4; i++) {
                    for(int j = 0; j < 4; j++) {
                        res(i,j) = operator()(j,i);
                    }
                }
                return res;
            }

            static Mat4x4<T> identity() {
                T arr[16] = { 1, 0, 0, 0,
                              0, 1, 0, 0,
                              0, 0, 1, 0,
                              0, 0, 0, 1 };
                return Mat4x4<T>(arr);
            }

            friend Mat4x4<T> operator+(Mat4x4<T> lhs,
                                       const Mat4x4<T> rhs) {
                for(int i = 0; i < 16; i++) {
                    lhs.m[i] += rhs.m[i];
                }
                return lhs;
            }
            friend Mat4x4<T> operator-(Mat4x4<T> lhs,
                                       const Mat4x4<T> rhs) {
                for(int i = 0; i < 16; i++) {
                    lhs.m[i] -= rhs.m[i];
                }
                return lhs;
            }

            friend Mat4x4<T> operator*(const T lhs, Mat4x4<T> rhs) {
                for(int i = 0; i < 16; i++) {
                    rhs.m[i] *= lhs;
                }
                return rhs;
            }

            friend Mat4x4<T> operator*(Mat4x4<T> lhs, const T rhs) {
                return operator*(rhs, lhs);
            }

            friend Vector4<T> operator*(const Mat4x4<T> lhs,
                                        const Vector4<T> rhs) {
                Vector4<T> res(
                    lhs.m[ 0]*rhs.x+lhs.m[ 1]*rhs.y+lhs.m[ 2]*rhs.z+lhs.m[ 3]*rhs.w,
                    lhs.m[ 4]*rhs.x+lhs.m[ 5]*rhs.y+lhs.m[ 6]*rhs.z+lhs.m[ 7]*rhs.w,
                    lhs.m[ 8]*rhs.x+lhs.m[ 9]*rhs.y+lhs.m[10]*rhs.z+lhs.m[11]*rhs.w,
                    lhs.m[12]*rhs.x+lhs.m[13]*rhs.y+lhs.m[14]*rhs.z+lhs.m[15]*rhs.w
                    );
                return res;
            }

            friend Mat4x4<T> operator*(const Mat4x4<T> lhs,
                                       const Mat4x4<T> rhs) {
                Mat4x4<T> res;
                for(int i = 0; i < 4; i++) {
                    for(int j = 0; j < 4; j++) {
                        res(i, j) = 0;
                        for(int k = 0; k < 4; k++) {
                            res(i, j) += lhs(i, k) * rhs(k, j);
                        }
                    }
                }
                return res;
            }

            T& operator()(size_t row, size_t col) {
                return m[4*row+col];
            }
            const T& operator()(size_t row, size_t col) const {
                return m[4*row+col];
            }

            T& operator[](size_t index) {
                return m[index];
            }
            const T& operator[](size_t index) const {
                return m[index];
            }

    };

    typedef Mat4x4<float> mat4x4f;
    typedef Mat4x4<int>   mat4x4i;

    template<class T>
    inline std::ostream& operator<<(std::ostream& str, Vector3<T> const& v) {
        str << v.x << " " << v.y << " " << v.z;
        return str;
    }

    template<class T>
    inline std::ostream& operator<<(std::ostream& str, Vector4<T> const& v) {
        str << v.x << " " << v.y << " " << v.z << " " << v.w;
        return str;
    }

    template<class T>
    inline std::ostream& operator<<(std::ostream& str, Mat4x4<T> const& v) {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                str << v(i,j) << " ";
            }
            str << std::endl;
        }
        return str;
    }
};


#endif // __MATH3D_H_
