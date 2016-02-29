#include "foresight/resource.h"

namespace fore {

Resource::Resource(Id id, std::string name) :
    id_(id),
    name_(name) {}

bool has_enough(const Resource::Amount& source, 
                const Resource::Amount& required)
{
  for (const auto& key : required)
  {
    Resource::Id id = key.first;
    int amount = key.second;
    if (source.count(id) == 0 || source.at(id) < amount) {
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
