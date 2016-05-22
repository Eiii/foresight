#include "foresight/policies/upfront.h"
#include "foresight/policies/uniform.h"
#include "foresight/nullaction.h"

#include <algorithm>
#include <cassert>
#include <cmath>

namespace fore {

Upfront::Upfront(const Domain& domain, ActionType::Id id1, ActionType::Id id2):
    Policy(domain),
    first_id_(id1),
    seq_id_(id2),
    uniform_policy_(new UniformPolicy(domain_, seq_id_))
{ }

Action::Ptr Upfront::SelectAction(const State& state)
{
  auto legal_actions(simulator_.LegalActions(state));

  //Calculate switching time
  int switch_time = domain_.action_type(first_id_).duration().mean();

  if (state.time() == 0) {
    //Start off the big initial batch
    int initial_batch = CalculateFirstBatchSize(state);
    if (ActionsStarted(state) < initial_batch) {
      return FindAction(state, first_id_);
    }
  } else if (state.time() > switch_time) {
    return uniform_policy_->SelectAction(state);
  }

  return FindNullAction(state);
}

int Upfront::CalculateFirstBatchSize(const State& state) const
{
  const auto& action_type(domain_.action_type(first_id_));
  const auto& seq_type(domain_.action_type(seq_id_));
  int horizon_left(domain_.horizon() - action_type.duration().mean());
  int max_exe(horizon_left / seq_type.duration().mean());
  auto res_required(seq_type.requires() * max_exe);
  auto res_leftover(state.resources() - res_required);
  return res_leftover / action_type.requires();
}

int Upfront::ActionsStarted(const State& state) const
{
  int num_started(0);
  for (const auto& action_ptr : state.running_actions()) {
    if (action_ptr->type_id() == first_id_) {
      num_started++;
    }
  }
  return num_started;
}

}
