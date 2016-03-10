#include "foresight/experimentactiontype.h"

#include <iostream>

namespace fore {

//TODO: Add model info
ExperimentActionType::ExperimentActionType(
  ActionType::Id id, std::string name, Duration duration, bool cancelable,
  Resource::Amount requires, 
  Resource::Amount produces, 
  Resource::Amount upkeep,
  Model::Id model_id
) :
    ActionType(id, name, duration, cancelable, requires, produces, upkeep),
    model_id_(model_id) {}
    
std::vector<Action::Ptr> 
    ExperimentActionType::GenerateActions(const State& state) const
{
  //TODO: Generate 'base' action
  //TODO: Calculate best input point on model
  //TODO: Build/return resultant action 
  return ActionType::GenerateActions(state);
}

State ExperimentActionType::Start(
    const Action& action, const State& state) const
{
  //TODO: Update model w/ false observation
  return ActionType::Start(action, state);
}

void ExperimentActionType::End(const Action& action, StateFactory* fact) const
{
  //TODO: 'base' End
  //TODO: Remove false observation
  //TODO: Calculate+add model observation
  ActionType::End(action, fact);
}

State ExperimentActionType::Cancel(
    const Action& target, const State& state) const
{
  return ActionType::Cancel(target, state);
}

}
