#include "foresight/policies/uniform.h"
#include "foresight/nullaction.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

namespace fore {

UniformPolicy::UniformPolicy(const Domain& domain, ActionType::Id action_id) :
    Policy(domain), action_id_(action_id) {}

Action::Ptr UniformPolicy::SelectAction(const State& state)
{
  //This policy only makes sense when we can execute the null action
  assert(domain_.has_null_action());

  //Count the number of actions currently running
  auto num_started(ActionsStarted(state));

  //Count the total number of actions we can execute with our current budget
  auto remaining(TotalRemaining(state));

  //Figure out how many we want running per timestep
  auto time_left(domain_.horizon() - state.time());
  auto duration(domain_.action_type(action_id_).duration().mean());
  auto num_left((double)time_left/duration);
  auto per_step(static_cast<int>(std::ceil(remaining/num_left)));

  auto legal_actions(simulator_.LegalActions(state));
  if (num_started < per_step) {
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

int UniformPolicy::ActionsStarted(const State& state) 
{
  int num_started(0);
  for (const auto& action_ptr : state.running_actions()) {
    if (action_ptr->type_id() == action_id_) {
      num_started++;
    }
  }
  return num_started;
}

int UniformPolicy::TotalRemaining(const State& state) 
{
  //Calculate limiting resource
  int max_num = std::numeric_limits<int>::max();
  const auto& action_type(domain_.action_type(action_id_));
  const auto& requires(action_type.requires());
  const auto& current_res(state.resources());

  for (const auto& key : requires) {
    auto id = key.first;
    auto amt = key.second;
    double max;
    if (current_res.count(id)) {
      max = (double)current_res.at(id) / amt; 
    } else {
      max = 0.0;
    }
    max = std::floor(max);
    if (max < max_num) max_num = static_cast<int>(max);
  }
  return max_num;
}

}
