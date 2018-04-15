#pragma once

#include "Vec3D.h"

struct Ray {
  constexpr Vec3dD at(double t) const { return origin + t * direction; }

  Vec3dD origin;
  Vec3dD direction;
};

Ray computeRayFrom2Points(const Vec3dD& p0, const Vec3dD& p1) {
  return {p0, (p1 - p0).normalized()};
}
