#pragma once

#include <optional>
#include "HitResult.h"
#include "Ray.h"
#include "Utils.h"
#include "Vec3D.h"

struct ScatterResult {
  Ray scattered;
  Vec3dD attenuation;
};

struct Material {
  virtual std::optional<ScatterResult> scatter(const Ray& ray,
                                               const HitResult& h) const = 0;
};

struct Lambertian : Material {
  Lambertian(const Vec3dD& v) : albedo(v) {}
  std::optional<ScatterResult> scatter(const Ray& ray,
                                       const HitResult& h) const override {
    ScatterResult results;
    results.attenuation = albedo;
    const auto target = h.point + h.normal + randomPointInUnitSphere();
    results.scattered = computeRayFrom2Points(h.point, target);
    return results;
  }
  Vec3dD albedo;
};

struct Metal : Material {
  Metal(const Vec3dD& v) : albedo(v) {}
  std::optional<ScatterResult> scatter(const Ray& ray,
                                       const HitResult& h) const override {
    ScatterResult results;
    results.attenuation = albedo;
    const auto reflected = reflect(ray.direction, h.normal).normalized();
    results.scattered = Ray{h.point, reflected};
    if (reflected.dot(h.normal) > 0) return results;
    return std::nullopt;
  }
  Vec3dD albedo;
};