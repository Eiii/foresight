#include "foresight/policies/mei.h"

#include "foresight/experimentaction.h"

#include <algorithm>
#include <cassert>

namespace fore {

MEIPolicy::MEIPolicy(const Domain& domain) :
    Policy(domain) {}

Action::Ptr MEIPolicy::SelectAction(const State& state)
{
  auto legal_actions(simulator_.LegalActions(state));
  decltype(legal_actions) exp_actions;

  //Filter out non-experiment actions
  for (const auto& action : legal_actions) {
    if (is_experiment_action(*action)) {
      exp_actions.emplace_back(action->Clone());
    }
  }
  //Check that we have at least one action
  assert(exp_actions.size() > 0);

  //Take the MEI action
  //TODO
  return exp_actions[0]->Clone();
}

}
