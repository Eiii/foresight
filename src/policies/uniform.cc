#include "foresight/policies/uniform.h"
#include "foresight/nullaction.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

using std::vector;
using std::endl;
using std::cout;

namespace fore {

UniformPolicy::UniformPolicy(const Domain& domain, ActionType::Id action_id) :
    Policy(domain), action_id_(action_id),
    actions_per_step_(CalcActionsPerStep(domain)) {}

Action::Ptr UniformPolicy::SelectAction(const State& state)
{
  //This policy only makes sense when we can execute the null action
  assert(domain_.has_null_action());

  //Count the number of actions currently running
  auto num_started(ActionsStarted(state));

  auto legal_actions(simulator_.LegalActions(state));
  if (num_started < actions_per_step_.at(state.time())) {
    for (auto& action_ptr : legal_actions) {
      if (action_ptr->type_id() == action_id_) {
        return std::move(action_ptr);
      }
    }
  } else {
    for (auto& action_ptr : legal_actions) {
      if (is_null_action(*action_ptr)) {
        return std::move(action_ptr);
      }
    }
  }

  //Couldn't find desired action-- give up!
  assert(false);
  return legal_actions[0]->Clone();
}

Policy::Ptr UniformPolicy::Clone() const
{
  return std::make_unique<UniformPolicy>(*this);
}

int UniformPolicy::ActionsStarted(const State& state) const
{
  int num_started(0);
  for (const auto& action_ptr : state.running_actions()) {
    if (action_ptr->type_id() == action_id_) {
      num_started++;
    }
  }
  return num_started;
}

vector<int> UniformPolicy::CalcActionsPerStep(const Domain& domain) const
{
  auto horizon(domain.horizon());
  const auto& action(domain_.action_type(action_id_));
  auto timesteps(horizon/action.duration().mean());
  auto inital_amt(domain.initial_state().resources());
  auto u(inital_amt/(action.requires()*timesteps));
  auto aps(vector<int>(horizon+1, 0));
  cout << timesteps << " / " << u << endl;
  for (int t = 0; t < domain.horizon(); t++) {
    aps[t] = u; 
  }
  return aps;
}

}
