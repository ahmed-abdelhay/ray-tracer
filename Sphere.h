#pragma once

#include <optional>
#include "Color.h"
#include "HitResult.h"
#include "Ray.h"
#include "Vec3D.h"

struct Sphere {
  double radius;
  Vec3dD centre;
};

std::optional<HitResult> intersects(const Sphere& s, const Ray& r, double tMin,
                                    double tMax) {
  const auto oc = r.origin - s.centre;
  const auto a = r.direction.dot(r.direction);
  const auto b = 2.0 * oc.dot(r.direction);
  const auto c = oc.dot(oc) - (s.radius * s.radius);
  const auto discriminant = b * b - (4 * a * c);

  auto computeHitResults = [&](double t) -> std::optional<HitResult> {
    if (t < tMax && t > tMin) {
      HitResult result;
      result.t = t;
      result.point = r.at(t);
      result.normal = (result.point - s.centre).normalized();
      return result;
    }
    return std::nullopt;
  };

  if (discriminant >= 0.0) {
    if (const auto r =
            computeHitResults((-b - std::sqrt(discriminant)) / (2 * a)))
      return r;
    if (const auto r =
            computeHitResults((-b + std::sqrt(discriminant)) / (2 * a)))
      return r;
  }
  return std::nullopt;
}
