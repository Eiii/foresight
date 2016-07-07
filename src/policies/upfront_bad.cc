#include "foresight/policies/upfront_bad.h"
#include "foresight/nullaction.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

using std::vector;

namespace fore {

UpfrontBadPolicy::UpfrontBadPolicy(const Domain& domain, ActionType::Id id1) :
    UniformPolicy(domain, id1)
{
  actions_per_step_ = CalcActionsPerStep(domain_);
}

Policy::Ptr UpfrontBadPolicy::Clone() const
{
  return std::make_unique<UpfrontBadPolicy>(*this);
}

vector<int> UpfrontBadPolicy::CalcActionsPerStep(const Domain& domain) const
{
  auto horizon(domain.horizon());
  const auto& action(domain_.action_type(action_id_));
  auto timesteps(horizon/action.duration().mean());
  auto initial_amt(domain.initial_state().resources());
  auto duration(action.duration().mean());

  auto aps(vector<int>(horizon+1, 0));
  for (int t = 0; t < horizon; t++) aps[t] = 1;

  auto req(action.requires());
  auto leftover(initial_amt-req*timesteps);

  aps[horizon-duration] += leftover/req;
  return aps;
}

}
