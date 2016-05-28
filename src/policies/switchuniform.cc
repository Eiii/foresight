#include "foresight/policies/switchuniform.h"
#include "foresight/nullaction.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>

namespace fore {

SwitchUniformPolicy::SwitchUniformPolicy(
    const Domain& domain, ActionType::Id id1, ActionType::Id id2, int time
) :
    Policy(domain),
    policy1_(new UniformPolicy(domain_, id1)),
    policy2_(new UniformPolicy(domain_, id2)),
    switch_time_(time) { } 

SwitchUniformPolicy::SwitchUniformPolicy(const SwitchUniformPolicy& rhs) :
    Policy(rhs),
    policy1_(rhs.policy1_->Clone()), 
    policy2_(rhs.policy2_->Clone()), 
    switch_time_(rhs.switch_time_) { }

SwitchUniformPolicy& SwitchUniformPolicy::operator=
  (
    const SwitchUniformPolicy& rhs
  )
{
  SwitchUniformPolicy p(rhs);
  std::swap(*this, p);
  return *this;
}

Action::Ptr SwitchUniformPolicy::SelectAction(const State& state)
{
  if (state.time() < switch_time_) {
    return policy1_->SelectAction(state);
  } else {
    return policy2_->SelectAction(state);
  }
}

Policy::Ptr SwitchUniformPolicy::Clone() const
{
  return std::make_unique<SwitchUniformPolicy>(*this);
}

}
