#include "foresight/policies/pair.h"

#include "foresight/experimentaction.h"

static bool has_exp_actions(const std::vector<fore::Action::Ptr>& actions);

namespace fore {

PairPolicy::PairPolicy(const Domain& domain, 
                       Policy::Ptr&& exp, Policy::Ptr&& res) :
    Policy(domain), exp_policy_(move(exp)), res_policy_(move(res)) {};

Action::Ptr PairPolicy::SelectAction(const State& state) 
{
  auto actions = simulator_.LegalActions(state);
  if (has_exp_actions(actions)) {
    return exp_policy_->SelectAction(state);
  } else {
    return res_policy_->SelectAction(state);
  }
}

}

static bool has_exp_actions(const std::vector<fore::Action::Ptr>& actions)
{
  for (const auto& action : actions) {
    if (fore::is_experiment_action(*action)) return true;
  }
  return false;
}
