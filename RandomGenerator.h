#pragma once

#include <chrono>
#include <random>

struct RandomGenerator {
  RandomGenerator(double start = 0.0, double end = 1.0) : uniform(start, end) {
    // initialize the random number generator with time-dependent seed
    const auto seed =
        std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(seed & 0xffffffff), uint32_t(seed >> 32)};
    range.seed(ss);
  }

  double generate() { return uniform(range); }

 private:
  std::mt19937_64 range;
  std::uniform_real_distribution<double> uniform;
};
