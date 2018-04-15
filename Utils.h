#pragma once

#include "RandomGenerator.h"
#include "Vec3D.h"

Vec3dD interpolate(const Vec3dD& start, const Vec3dD& end, double t) {
  return (1 - t) * start + t * end;
}

Vec3dD randomPointInUnitSphere() {
  RandomGenerator g(-1, 1);
  Vec3dD p;
  do
    p = Vec3dD{g.generate(), g.generate(), g.generate()};
  while (p.normSquared() >= 1.0);
  return p;
}
