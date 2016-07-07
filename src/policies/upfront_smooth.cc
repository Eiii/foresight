#include "foresight/policies/upfront_smooth.h"
#include "foresight/nullaction.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

using std::vector;

namespace fore {

UpfrontSmoothPolicy::UpfrontSmoothPolicy(
    const Domain& domain, ActionType::Id id
) :
    UniformPolicy(domain, id)
{
  actions_per_step_ = CalcActionsPerStep(domain_);
}

Policy::Ptr UpfrontSmoothPolicy::Clone() const
{
  return std::make_unique<UpfrontSmoothPolicy>(*this);
}

vector<int> UpfrontSmoothPolicy::CalcActionsPerStep(const Domain& domain) const
{
  auto horizon(domain.horizon());
  const auto& action(domain_.action_type(action_id_));
  auto duration(action.duration().mean());
  auto timesteps(horizon/duration);
  auto initial_amt(domain.initial_state().resources());

  auto aps(vector<int>(horizon+1, 0));
  for (int t = 0; t < horizon; t++) aps[t] = 1;

  auto req(action.requires());
  auto leftover_res(initial_amt-req*timesteps);
  auto remaining_exp(leftover_res/req);
  auto width(static_cast<int>(sqrt(2*remaining_exp)));
  auto height(width);

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < duration; j++) {
      auto t = i*duration+j;
      aps[t] += height-i;
    }
  }
  return aps;
}

}
