#include "foresight/experimentactiontype.h"

namespace fore {

ExperimentActionType::ExperimentActionType(
  ActionType::Id id, std::string name, Duration duration, bool cancelable,
  Resource::Amount requires, 
  Resource::Amount produces, 
  Resource::Amount upkeep
) :
    ActionType(id, name, duration, cancelable, requires, produces, upkeep) {}
    
std::vector<Action::Ptr> 
    ExperimentActionType::GenerateActions(const State& state) const
{
  return ActionType::GenerateActions(state);
}

State ExperimentActionType::Start(
    const Action& action, const State& state) const
{
  return ActionType::Start(action, state);
}

void ExperimentActionType::End(const Action& action, StateFactory* fact) const
{
  ActionType::End(action, fact);
}

State ExperimentActionType::Cancel(
    const Action& target, const State& state) const
{
  return ActionType::Cancel(target, state);
}

}
