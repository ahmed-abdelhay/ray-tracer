#pragma once

#include <algorithm>
#include <array>
#include <cmath>

template <typename T = double>
struct Vec3D {
  union {
    std::array<T, 3> v;
    struct {
      T x;
      T y;
      T z;
    };
  };

  constexpr Vec3D(const T& x = 0, const T& y = 0, const T& z = 0)
      : v({x, y, z}) {}

  constexpr T norm() const { return std::sqrt(normSquared()); }
  constexpr T normSquared() const { return dot(*this); }

  constexpr void normalize() {
    const auto n = norm();
    std::for_each(v.begin(), v.end(), [&n](auto& c) { c /= n; });
  }

  constexpr Vec3D normalized() const {
    const auto n = norm();
    return {x / n, y / n, z / n};
  }

  constexpr T dot(const Vec3D& v) const { return v.x * x + v.y * y + v.z * z; }
  constexpr T cross(const Vec3D& v) const {
    return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
  }

  constexpr T& operator[](size_t i) { return v[i]; }
  constexpr const T& operator[](size_t i) const { return v[i]; }

  constexpr Vec3D operator-() const { return {-x, -y, -z}; }

  constexpr Vec3D operator+=(const Vec3D& v) {
    x += v.x;
    y += v.y;
    z += v.z;
  }
  constexpr Vec3D operator-=(const Vec3D& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
  }
  constexpr Vec3D operator*=(double f) {
    x *= f;
    y *= f;
    z *= f;
  }
  constexpr Vec3D operator/=(double f) {
    x /= f;
    y /= f;
    z /= f;
  }
};

template <typename T>
constexpr Vec3D<T> operator+(const Vec3D<T>& v1, const Vec3D<T>& v2) {
  return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}
template <typename T>
constexpr Vec3D<T> operator-(const Vec3D<T>& v1, const Vec3D<T>& v2) {
  return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}
template <typename T>
constexpr Vec3D<T> operator*(const Vec3D<T>& v1, const Vec3D<T>& v2) {
  return {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}
template <typename T>
constexpr Vec3D<T> operator/(const Vec3D<T>& v1, const Vec3D<T>& v2) {
  return {v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};
}
template <typename T>
constexpr Vec3D<T> operator*(const Vec3D<T>& v, double f) {
  return {v.x * f, v.y * f, v.z * f};
}
template <typename T>
constexpr Vec3D<T> operator/(const Vec3D<T>& v, double f) {
  return {v.x / f, v.y / f, v.z / f};
}
template <typename T>
constexpr Vec3D<T> operator*(double f, const Vec3D<T>& v) {
  return v * f;
}
template <typename T>
constexpr Vec3D<T> operator/(double f, const Vec3D<T>& v) {
  return v / f;
}

using Vec3dD = Vec3D<double>;
