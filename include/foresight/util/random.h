#pragma once

#include <boost/random.hpp>

namespace fore {

using RandomEngine = boost::mt19937;
using UniformIntDist = boost::uniform_int<>;
using UniformRealDist = boost::uniform_real<>;
using RandomInt = boost::variate_generator<RandomEngine&, UniformIntDist>;
using RandomReal = boost::variate_generator<RandomEngine&, UniformRealDist>;

}
