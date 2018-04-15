#pragma once

#include "Ray.h"
#include "Vec3D.h"

struct Camera {
  Vec3dD origin;
  Vec3dD xDirection;
  Vec3dD yDirection;
  Vec3dD startPoint;

  Ray ray(double u, double v) const {
    return {origin,
            (startPoint + u * xDirection + v * yDirection).normalized()};
  }
};
