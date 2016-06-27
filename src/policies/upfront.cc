#include "foresight/policies/upfront.h"
#include "foresight/policies/uniform.h"
#include "foresight/nullaction.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

using std::vector;

namespace fore {

UpfrontPolicy::UpfrontPolicy(const Domain& domain, ActionType::Id id1) :
    UniformPolicy(domain, id1)
{
  actions_per_step_ = CalcActionsPerStep(domain_);
}

Policy::Ptr UpfrontPolicy::Clone() const
{
  return std::make_unique<UpfrontPolicy>(*this);
}

vector<int> UpfrontPolicy::CalcActionsPerStep(const Domain& domain) const
{
  auto aps(vector<int>(domain.horizon()+1, 0));
  std::cout << "Upfront APS" << std::endl;
  return aps;
}

}
