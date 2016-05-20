#include "foresight/policies/switchuniform.h"
#include "foresight/nullaction.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

namespace fore {

SwitchUniformPolicy::SwitchUniformPolicy(
    const Domain& domain, ActionType::Id id1, ActionType::Id id2, int time
) :
    Policy(domain),
    policy1_(new UniformPolicy(domain_, id1)),
    policy2_(new UniformPolicy(domain_, id2)),
    switch_time_(time)
{ }

Action::Ptr SwitchUniformPolicy::SelectAction(const State& state)
{
  if (state.time() < switch_time_) {
    return policy1_->SelectAction(state);
  } else {
    return policy2_->SelectAction(state);
  }
}

}
