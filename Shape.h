#pragma once
#include <optional>
#include "HitResult.h"
#include "Ray.h"

struct Shape {
  virtual std::optional<HitResult> intersects(const Ray& r, double tMin,
                                              double tMax) const = 0;
};
