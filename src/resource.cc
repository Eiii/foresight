#include "foresight/resource.h"

namespace fore {

Resource::Resource(Id id, std::string name) :
    id_(id),
    name_(name) {}

bool has_enough(const Resource::Amount& available, 
                const Resource::Amount& required)
{
  for (const auto& key : required)
  {
    Resource::Id id = key.first;
    int needed = key.second;
    int current = available.count(id) ? available.at(id) : 0;
    if (current < needed) {
      return false;
    }
  }
  return true;
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

}
