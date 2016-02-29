#include "foresight/actiontype.h"

#include "foresight/statefactory.h"

#include <algorithm>
#include <cassert>

namespace fore {

ActionType::ActionType(Id id, std::string name, Duration duration,
                       Resource::Amount requires,
                       Resource::Amount produces,
                       Resource::Amount upkeep) :
    id_(id), name_(name), duration_(duration), requires_(requires),
    produces_(produces), upkeep_(upkeep) {}

State ActionType::Start(const Action& action, const State& state) const
{
  StateFactory factory(state);
  //Verify we actually have enough resources to start the action
  assert(has_enough(state.resources(), requires_));
  //Subtract those resources
  auto res_available = state.resources() - requires_;
  factory.set_resources(std::move(res_available));
  //Add the action
  auto actions = state.running_actions();
  actions.push_back(action);
  factory.set_running_actions(std::move(actions));
  return factory.Finish();
}

void ActionType::End(const Action& action, StateFactory* fact) const
{
  auto current_resources(fact->resources());
  //Add produced resources
  fact->set_resources(current_resources + produces_);
  //Remove finished action
  auto actions(fact->running_actions());
  auto it = std::find(actions.cbegin(), actions.cend(), action);
  assert(it != actions.cend());
  actions.erase(it);
  fact->set_running_actions(std::move(actions));
}

}
