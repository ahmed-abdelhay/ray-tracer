#include <limits>
#include "Camera.h"
#include "Image.h"
#include "RandomGenerator.h"
#include "Ray.h"
#include "Sphere.h"
#include "Utils.h"
#include "Vec3D.h"

Color<double> calculateColor(const Ray &ray, const std::vector<Sphere> &objects,
                             size_t depth = 0) {
  constexpr auto tMin = 0.0;
  constexpr auto tMax = std::numeric_limits<double>::max();

  std::optional<HitResult> result;
  Material *material = nullptr;
  for (const auto &obj : objects) {
    const auto r = obj.intersects(ray, tMin, tMax);
    if (!result && r) {
      result = r;
      material = obj.material ? obj.material.get() : nullptr;
    } else if (result && r && r->t < result->t) {
      result = r;
      material = obj.material ? obj.material.get() : nullptr;
    }
  }

  if (!result) {
    // background
    const auto t = 0.5 * (ray.direction.y + 1.0);
    return interpolate(white, blue, t);
  }

  std::optional<ScatterResult> r;
  if (depth < 50 && material && (r = material->scatter(ray, *result))) {
    return r->attenuation * calculateColor(r->scattered, objects, depth + 1);
  }
  return black;
}

int main() {
  Image<double> image;
  image.rows = 200;
  image.cols = 100;
  image.buffer.resize(image.rows * image.cols);

  std::vector<Sphere> objects(4);
  objects[0].centre = Vec3dD{0, 0, -1};
  objects[0].radius = 0.5;
  objects[0].material = std::make_unique<Lambertian>(Vec3dD{0.8, 0.3, 0.3});

  objects[1].centre = Vec3dD{0, -100.5, -1};
  objects[1].radius = 100;
  objects[1].material = std::make_unique<Lambertian>(Vec3dD{0.8, 0.8, 0});

  objects[2].centre = Vec3dD{1, 0, -1};
  objects[2].radius = 0.5;
  objects[2].material = std::make_unique<Metal>(Vec3dD{0.8, 0.6, 0.2});

  objects[3].centre = Vec3dD{-1, 0, -1};
  objects[3].radius = 0.5;
  objects[3].material = std::make_unique<Metal>(Vec3dD{0.8, 0.8, 0.8});

  const Vec3dD xDirection{-4.0, 0.0, 0.0};
  const Vec3dD yDirection{0.0, -2.0, 0.0};
  const Vec3dD origin{0.0, 0.0, 0.0};
  const Vec3dD topLeftCorner{2.0, 1.0, -1.0};
  const Camera camera{origin, xDirection, yDirection, topLeftCorner};

  const auto xStep = 1.0 / image.rows;
  const auto yStep = 1.0 / image.cols;

  constexpr auto samplesCount = 100;
  RandomGenerator rand;

  for (size_t x = 0; x < image.rows; ++x) {
    for (size_t y = 0; y < image.cols; ++y) {
      Color<double> color;
      for (size_t s = 0; s < samplesCount; ++s) {
        const auto u = xStep * (x + rand.generate());
        const auto v = yStep * (y + rand.generate());
        const auto ray = camera.ray(u, v);
        color += calculateColor(ray, objects);
      }
      std::for_each(color.v.begin(), color.v.end(), [&samplesCount](auto &v) {
        v = std::sqrt(v / samplesCount);
      });
      image.buffer[x * image.cols + y] = color;
    }
  }

  writeImageToFile(image, "/home/ahmed/Desktop/ray-tracer/image.ppm");
  return EXIT_SUCCESS;
}
