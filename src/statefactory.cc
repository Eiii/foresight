#include "foresight/statefactory.h"

namespace fore {

StateFactory::StateFactory() :
    StateFactory(0) {}

StateFactory::StateFactory(const State& state) :
    timestep_(state.timestep()), 
    resources_(state.resources()), 
    running_actions_(state.running_actions()) {}

StateFactory::StateFactory(int timestep) :
    timestep_(timestep), resources_(), running_actions_() {}

State StateFactory::Finish() const
{
  return State(timestep_, resources_, running_actions_);
}

void StateFactory::Reset()
{
  timestep_ = 0;
  resources_.clear();
  running_actions_.clear();
}

void StateFactory::Copy(const State& state)
{
  timestep_ = state.timestep();
  resources_ = state.resources();
  running_actions_ = state.running_actions();
}

void StateFactory::SetResourceAmount(Resource::Id id, int amount)
{
  resources_[id] = amount;
}

}
