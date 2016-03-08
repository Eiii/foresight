#include "foresight/simulator.h"

#include "foresight/cancelaction.h"
#include "foresight/statefactory.h"

#include <cassert>

using std::make_unique;

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
      const auto& atype(domain_.action_type(action.type_id()));
      atype.End(action, &state_fact);
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
  const auto& atype(domain_.action_type(action.type_id()));
  const auto result_state(atype.Start(action, state));
  return result_state;
}

bool Simulator::IsDecisionPoint(const State& state) const
{
  for (const auto& key : domain_.action_types()) {
    const auto& atype = key.second;
    if (atype.CanStart(state)) {
      return true;
    }
  }
  return false;
}

std::vector<Action::Ptr> Simulator::LegalActions(const State& state) const
{
  (void)state;
  std::vector<Action::Ptr> actions;
  for (const auto& key : domain_.action_types()) {
    const auto& atype(key.second);
    if (!atype.CanStart(state)) continue;
    auto type_actions(atype.GenerateActions(state));
    std::move(type_actions.begin(), 
              type_actions.end(), 
              std::back_inserter(actions));
  }

  //Generate cancel actions
  for (const auto& action : state.running_actions()) {
    ActionType::Id id = action.type_id();
    if (domain_.action_type(id).cancelable()) {
      actions.emplace_back(make_unique<CancelAction>(state.time(), action));
    }
  }
  return actions;
}

bool Simulator::IsActionFinished(const Action& action, 
                                 const State& state) const
{
  const auto& atype(domain_.action_type(action.type_id()));
  auto duration(atype.duration().mean());
  return state.time() >= action.time_started() + duration;
}

}
