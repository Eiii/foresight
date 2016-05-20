#include "foresight/actiontype.h"

#include "foresight/statefactory.h"

#include <algorithm>
#include <cassert>
#include <memory>

static void remove_action(fore::StateFactory* fact, 
                          const fore::Action& target);

namespace fore {

ActionType::ActionType(Id id, std::string name, Duration duration,
                       bool cancelable,
                       Resource::Amount requires,
                       Resource::Amount produces,
                       Resource::Amount upkeep) :
    id_(id), name_(name), duration_(duration), cancelable_(cancelable),
    requires_(requires), produces_(produces), upkeep_(upkeep) {}

bool ActionType::CanStart(const State& state) const
{
  const auto& available = state.resources();
  return has_enough(available, requires_);
}

std::vector<Action::Ptr> ActionType::GenerateActions(
    const State& state, const Domain& domain
) const
{
  (void)domain;
  std::vector<Action::Ptr> actions;
  actions.emplace_back(std::make_unique<Action>(id_, state.time()));
  return actions;
}

State ActionType::Start(const Action& action, const Domain& domain, 
                        const State& state) const
{
  (void)domain;
  //Verify we actually have enough resources to start the action
  assert(has_enough(state.resources(), requires_));
  StateFactory factory(state);
  //Subtract those resources
  auto res_available = factory.resources() - requires_;
  factory.set_resources(std::move(res_available));
  //Add the action
  auto actions(copy_actions(state.running_actions()));
  actions.emplace_back(action.Clone());
  factory.set_running_actions(std::move(actions));
  return factory.Finish();
}

void ActionType::End(const Action& action, const Domain& domain, 
                     const State& state, StateFactory* fact) const
{
  (void)domain; (void)state;
  auto current_resources(fact->resources());
  //Add produced resources
  fact->set_resources(current_resources + produces_);
  //Remove finished action
  remove_action(fact, action);
}

State ActionType::Cancel(const Action& target, const State& state) const
{
  StateFactory factory(state);
  remove_action(&factory, target);
  return factory.Finish();
}

Action::List copy_actions(const fore::Action::List& actions)
{
  fore::Action::List list;
  for (const auto& action_p : actions) {
    list.emplace_back(action_p->Clone());
  }
  return list;
}

}

static void remove_action(fore::StateFactory* fact, const fore::Action& target)
{
  auto actions(copy_actions(fact->running_actions()));
  auto it(actions.cbegin());
  for (; it != actions.cend(); ++it) {
    if (**it == target) break;
  }
  assert(it != actions.cend());
  actions.erase(it);
  fact->set_running_actions(std::move(actions));
}


