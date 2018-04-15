#include <algorithm>
#include <fstream>
#include <string>
#include <type_traits>
#include <vector>

#include "Color.h"

template <typename T = double>
struct Image {
  using PixelType = T;

  std::vector<Color<T>> buffer;
  size_t rows{0};
  size_t cols{0};
};

template <typename T>
void writeImageToFile(const Image<T>& image, const std::string& fileName) {
  std::ofstream fout(fileName);
  fout << "P3"
       << "\n"
       << image.cols << " " << image.rows << "\n"
       << "255\n";
  for (size_t i = 0; i < image.rows; ++i) {
    for (size_t j = 0; j < image.cols; ++j) {
      const auto& v = image.buffer[i * image.cols + j];
      if constexpr(std::is_same_v<typename Image<T>::PixelType, double>) {
          const auto c = convertColorFormat(v);
          fout << static_cast<int>(c[0]) << " " << static_cast<int>(c[1]) << " "
               << static_cast<int>(c[2]) << " ";
        }
      else {
        fout << static_cast<int>(v[0]) << " " << static_cast<int>(v[1]) << " "
             << static_cast<int>(v[2]) << " ";
      }
    }
    fout << "\n";
  }
}
