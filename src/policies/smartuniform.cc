#include "foresight/policies/smartuniform.h"
#include "foresight/policies/uniform.h"
#include "foresight/nullaction.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

namespace fore {

SmartUniformPolicy::SmartUniformPolicy(
    const Domain& domain, ActionType::Id id1, ActionType::Id id2
) :
    Policy(domain),
    policy1_(new UniformPolicy(domain_, id1)),
    policy2_(new UniformPolicy(domain_, id2)),
    switched_(false)
{ }

SmartUniformPolicy::SmartUniformPolicy(const SmartUniformPolicy& rhs) :
    Policy(rhs),
    policy1_(rhs.policy1_->Clone()),
    policy2_(rhs.policy2_->Clone()),
    switched_(rhs.switched_) {}

SmartUniformPolicy& SmartUniformPolicy::operator=
  (
    const SmartUniformPolicy& rhs
  )
{
  SmartUniformPolicy p(rhs);
  std::swap(*this, p);
  return *this;
}

Action::Ptr SmartUniformPolicy::SelectAction(const State& state)
{
  //If we haven't switched yet, see if we should switch now
  if (!switched_) {
    //Run simulations of policies using our current understanding
    //of the problem as the 'real world'
    
    //If regret of policy2 < regret of policy1, switch!

  }
  
  
  if (!switched_) {
    return policy1_->SelectAction(state);
  } else {
    return policy2_->SelectAction(state);
  }
}

Policy::Ptr SmartUniformPolicy::Clone() const
{
  return std::make_unique<SmartUniformPolicy>(*this);
}

}
