#include <limits>
#include "Camera.h"
#include "Image.h"
#include "RandomGenerator.h"
#include "Ray.h"
#include "Sphere.h"
#include "Utils.h"
#include "Vec3D.h"

Color<double> calculateColor(const Ray &ray,
                             const std::vector<Sphere> &objects) {
  std::optional<HitResult> result;
  for (const auto &obj : objects) {
    if (const auto r =
            intersects(obj, ray, 0, std::numeric_limits<double>::max());
        !result && r) {
      result = r;
    } else if (result && r) {
      if (r->t < result->t) result = r;
    }
  }
  if (result) {
    const auto target =
        result->point + result->normal + randomPointInUnitSphere();
    return 0.5 * calculateColor(computeRayFrom2Points(result->point, target),
                                objects);
    // return (result->normal + Vec3dD{1, 1, 1}) * 0.5;
  }
  const auto t = 0.5 * (ray.direction.y + 1.0);
  return interpolate(white, blue, t);
}

int main() {
  Image<double> image;
  image.rows = 200;
  image.cols = 100;
  image.buffer.resize(image.rows * image.cols);

  const std::vector<Sphere> sceneObjects{{0.5, {0, 0, -1}},
                                         {100, {1, -100.5, -1}}};

  const Vec3dD xDirection{-4.0, 0.0, 0.0};
  const Vec3dD yDirection{0.0, -2.0, 0.0};
  const Vec3dD origin{0.0, 0.0, 0.0};
  const Vec3dD topLeftCorner{2.0, 1.0, -1.0};
  const Camera camera{origin, xDirection, yDirection, topLeftCorner};

  const auto xStep = 1.0 / image.rows;
  const auto yStep = 1.0 / image.cols;

  constexpr auto samplesCount = 5;
  RandomGenerator rand;

  for (size_t x = 0; x < image.rows; ++x) {
    for (size_t y = 0; y < image.cols; ++y) {
      Color<double> color;
      for (size_t s = 0; s < samplesCount; ++s) {
        const auto u = xStep * (x + rand.generate());
        const auto v = yStep * (y + rand.generate());
        const auto ray = camera.ray(u, v);
        color += calculateColor(ray, sceneObjects);
      }
      std::for_each(color.v.begin(), color.v.end(), [&samplesCount](auto &v) {
        v = std::sqrt(v / samplesCount);
      });
      image.buffer[x * image.cols + y] = color;
    }
  }

  writeImageToFile(image, "/home/ahmed/Desktop/ray_tracer/image.ppm");
  return EXIT_SUCCESS;
}
