#pragma once

#include "Vec3D.h"

struct Ray {
  constexpr Ray(const Vec3dD& o, const Vec3dD& d) : origin(o), direction(d) {}

  constexpr Vec3dD at(double t) const { return origin + t * direction; }

  const Vec3dD origin;
  const Vec3dD direction;
};

Ray computeRayFrom2Points(const Vec3dD& p0, const Vec3dD& p1) {
  return {p0, (p1 - p0).normalized()};
}
