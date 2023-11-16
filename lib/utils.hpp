#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <unordered_map>

namespace utils {
  template<std::size_t N>
  using AdjMatrix = std::array<std::array<int, N>, N>;
  void read(std::string filename);
}

#endif
