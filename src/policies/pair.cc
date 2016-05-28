#include "foresight/policies/pair.h"

#include "foresight/experimentaction.h"

static bool has_exp_actions(const std::vector<fore::Action::Ptr>& actions);

namespace fore {

PairPolicy::PairPolicy(const Domain& domain, 
                       Policy::Ptr&& exp, Policy::Ptr&& res) :
    Policy(domain), exp_policy_(move(exp)), res_policy_(move(res)) {};

PairPolicy::PairPolicy(const PairPolicy& rhs) :
    Policy(rhs), 
    exp_policy_(rhs.exp_policy_->Clone()), 
    res_policy_(rhs.res_policy_->Clone()) {}

PairPolicy& PairPolicy::operator=(const PairPolicy& rhs) {
  PairPolicy p(rhs);
  std::swap(*this, p);
  return *this;
}

Action::Ptr PairPolicy::SelectAction(const State& state) 
{
  auto actions = simulator_.LegalActions(state);
  if (has_exp_actions(actions)) {
    return exp_policy_->SelectAction(state);
  } else {
    return res_policy_->SelectAction(state);
  }
}

Policy::Ptr PairPolicy::Clone() const
{
  return std::make_unique<PairPolicy>(*this);
}

}

static bool has_exp_actions(const std::vector<fore::Action::Ptr>& actions)
{
  for (const auto& action : actions) {
    if (fore::is_experiment_action(*action)) return true;
  }
  return false;
}
