#pragma once

#include <iostream>
#include <vector>

namespace fore {

using Point = std::vector<double>;
using Obs = std::pair<Point, double>;
using ObsList = std::vector<Obs>;

std::ostream& operator<<(std::ostream& s, const Point& p);

}
