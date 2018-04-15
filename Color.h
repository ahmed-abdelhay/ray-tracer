#pragma once

#include "Vec3D.h"

template <typename T = double>
using Color = Vec3D<T>;

constexpr Color<double> red{1.0, 0.0, 0.0};
constexpr Color<double> green{0.0, 1.0, 0.0};
constexpr Color<double> blue{0.0, 0.0, 1.0};
constexpr Color<double> white{1.0, 1.0, 1.0};
constexpr Color<double> black{0.0, 0.0, 0.0};

constexpr Color<unsigned char> convertColorFormat(const Color<double>& c) {
  return {static_cast<unsigned char>(c[0] * 255),
          static_cast<unsigned char>(c[1] * 255),
          static_cast<unsigned char>(c[2] * 255)};
}

constexpr Color<double> convertColorFormat(const Color<unsigned char>& c) {
  return {c[0] / 255.0, c[1] / 255.0, c[2] / 255.0};
}
