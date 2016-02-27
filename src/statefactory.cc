#include "foresight/statefactory.h"

namespace fore {

StateFactory::StateFactory() :
    StateFactory(0) {}

StateFactory::StateFactory(const State& state) :
    time_(state.time()), 
    resources_(state.resources()), 
    running_actions_(state.running_actions()) {}

StateFactory::StateFactory(int time) :
    time_(time), resources_(), running_actions_() {}

State StateFactory::Finish() const
{
  return State(time_, resources_, running_actions_);
}

void StateFactory::Reset()
{
  time_ = 0;
  resources_.clear();
  running_actions_.clear();
}

void StateFactory::Copy(const State& state)
{
  time_ = state.time();
  resources_ = state.resources();
  running_actions_ = state.running_actions();
}

void StateFactory::SetResourceAmount(Resource::Id id, int amount)
{
  resources_[id] = amount;
}

}
