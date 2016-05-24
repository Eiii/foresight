#include "foresight/resource.h"

#include <algorithm>

namespace fore {

Resource::Resource(Id id, std::string name) :
    id_(id),
    name_(name) {}

bool has_enough(const Resource::Amount& available, 
                const Resource::Amount& required)
{
  return (available / required) > 0;
}

Resource::Amount operator-(const Resource::Amount& lhs, 
                           const Resource::Amount& rhs)
{
  Resource::Amount amt(lhs);
  for (const auto& key : rhs) {
    Resource::Id id = key.first;
    int res_amt = key.second;
    amt[id] -= res_amt;
  }
  return amt;
}

Resource::Amount operator+(const Resource::Amount& lhs, 
                           const Resource::Amount& rhs)
{
  Resource::Amount amt(lhs);
  for (const auto& key : rhs) {
    Resource::Id id = key.first;
    int res_amt = key.second;
    amt[id] += res_amt;
  }
  return amt;
}

Resource::Amount operator*(const Resource::Amount& lhs, int rhs)
{
  Resource::Amount amt;
  for (const auto& key : lhs) {
    Resource::Id id = key.first;
    int res_amt = key.second;
    amt[id] = res_amt * rhs;
  }
  return amt;
}

int operator/(const Resource::Amount& lhs, const Resource::Amount& rhs)
{
  int max_num = std::numeric_limits<int>::max();
  for (const auto& key : rhs) {
    auto id = key.first;
    auto amt = key.second;
    if (amt == 0) continue;
    int max;
    if (lhs.count(id)) {
      max = lhs.at(id) / amt; 
    } else {
      max = 0.0;
    }
    max = std::floor(max);
    if (max < max_num) max_num = max;
  }
  return max_num;
}

}
