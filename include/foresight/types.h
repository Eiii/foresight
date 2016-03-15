#pragma once

#include <vector>

namespace fore {
  using Point = std::vector<double>;
  using Obs = std::pair<Point, double>;
  using ObsList = std::vector<Obs>;
}
