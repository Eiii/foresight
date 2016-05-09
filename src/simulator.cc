#include "foresight/simulator.h"

#include "foresight/cancelaction.h"
#include "foresight/nullaction.h"
#include "foresight/statefactory.h"

#include <cassert>

#include <iostream>

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
  for (const auto& action_p : state.running_actions()) {
    if (IsActionFinished(*action_p, state)) {
      const auto& atype(domain_.action_type(action_p->type_id()));
      atype.End(*action_p, domain_, state, &state_fact);
    } else if (!is_null_action(*action_p)) {
      next_actions.emplace_back(action_p->Clone());
    }
  }
  state_fact.set_running_actions(std::move(next_actions));

  return state_fact.Finish();
}

State Simulator::BeginAction(const State& state, 
                             const Action& action) const
{
  if (is_cancel_action(action)) {
    //If we're canceling an action, we need to figure out what exactly the
    //'target' action is-- downcast so we can get that info.
    const auto& cancel = static_cast<const CancelAction&>(action);
    const auto& atype(domain_.action_type(cancel.type_id()));
    const auto result_state(atype.Cancel(cancel.target(), state));
    return result_state;  
  } else if (is_null_action(action)) {
    //Otherwise, if we're executing the null action, we can't call its type's
    //start function since there is no null action type! Just execute the 
    //mechanics here.
    StateFactory fact(state);
    auto actions(copy_actions(state.running_actions()));
    actions.emplace_back(action.Clone());
    fact.set_running_actions(std::move(actions));
    return fact.Finish();
  } else {
    assert(action.time_started() == state.time());
    const auto& atype(domain_.action_type(action.type_id()));
    const auto result_state(atype.Start(action, domain_, state));
    return result_state;
  }
}

bool Simulator::IsDecisionPoint(const State& state) const
{
  //If we executed a null action this timestep, we know we don't want to run
  //any other actions no matter what.
  for (const auto& action : state.running_actions()) {
    if (is_null_action(*action)) return false;
  }
  for (const auto& key : domain_.action_types()) {
    const auto& atype(*key.second);
    if (atype.CanStart(state)) {
      return true;
    }
  }
  return false;
}

std::vector<Action::Ptr> Simulator::LegalActions(const State& state) const
{
  std::vector<Action::Ptr> actions;
  for (const auto& key : domain_.action_types()) {
    const auto& atype(*key.second);
    if (!atype.CanStart(state)) continue;
    auto type_actions(atype.GenerateActions(state, domain_));
    std::move(type_actions.begin(), 
              type_actions.end(), 
              std::back_inserter(actions));
  }

  //Generate cancel actions
  for (const auto& action_p : state.running_actions()) {
    ActionType::Id id = action_p->type_id();
    if (!is_null_action(*action_p) && domain_.action_type(id).cancelable()) {
      actions.emplace_back(make_unique<CancelAction>(state.time(), *action_p));
    }
  }

  //Generate null action
  if (domain_.has_null_action()) {
    actions.emplace_back(make_unique<NullAction>(state.time()));
  }
  return actions;
}

bool Simulator::IsActionFinished(const Action& action, 
                                 const State& state) const
{
  if (is_null_action(action)) return false;
  const auto& atype(domain_.action_type(action.type_id()));
  auto duration(atype.duration().mean());
  return state.time() >= action.time_started() + duration;
}

}
