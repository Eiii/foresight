#include "foresight/simulator.h"

#include "foresight/statefactory.h"

#include <cassert>

namespace fore {

Simulator::Simulator(const Domain& domain) :
    domain_(domain) {}

State Simulator::AdvanceTime(const State& state) const
{
  StateFactory state_fact(state);

  //Advance time
  state_fact.set_time(state.time()+1);

  //Find all finished actions
  Action::List next_actions;
  for (const auto& action : state.running_actions()) {
    if (IsActionFinished(action, state)) {
      //TODO: Finish action
    } else {
      next_actions.emplace_back(action);
    }
  }
  state_fact.set_running_actions(next_actions);

  return state_fact.Finish();
}

State Simulator::BeginAction(const State& state, 
                             const Action& action) const
{
  assert(action.time_started() == state.time());
  (void)action;
  return state;
}

bool Simulator::IsActionFinished(const Action& action, 
                                 const State& state) const
{
  const auto& atype = domain_.action_type(action.type_id());
  auto duration = atype.duration().mean();
  return state.time() >= action.time_started() + duration;
}

}
