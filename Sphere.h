#pragma once

#include <memory>
#include <optional>
#include "Color.h"
#include "HitResult.h"
#include "Material.h"
#include "Ray.h"
#include "Shape.h"
#include "Vec3D.h"

struct Sphere : Shape {
  double radius;
  Vec3dD centre;
  std::unique_ptr<Material> material;

  std::optional<HitResult> intersects(const Ray& r, double tMin,
                                      double tMax) const override {
    const auto oc = r.origin - centre;
    const auto a = r.direction.dot(r.direction);
    const auto b = 2.0 * oc.dot(r.direction);
    const auto c = oc.dot(oc) - std::pow(radius, 2);
    const auto d = b * b - (4 * a * c);

    auto computeResults = [&](double t) -> std::optional<HitResult> {
      if (t < tMax && t > tMin) {
        HitResult result;
        result.t = t;
        result.point = r.at(t);
        result.normal = (result.point - centre).normalized();
        return result;
      }
      return std::nullopt;
    };

    if (d >= 0.0) {
      if (const auto r = computeResults((-b - std::sqrt(d)) / (2 * a)))
        return r;
      if (const auto r = computeResults((-b + std::sqrt(d)) / (2 * a)))
        return r;
    }
    return std::nullopt;
  }
};
