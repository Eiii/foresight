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

template<typename... Args>
void StateFactory::AddResource(Args&&... args)
{
  resources_.emplace(std::forward<Args>(args)...);
}

template<typename... Args>
void StateFactory::AddRunningAction(Args&&... args)
{
  running_actions_.emplace(std::forward<Args>(args)...);
}

template <typename T> 
void StateFactory::set_resources(T&& resources)
{
  resources_ = std::forward<T>(resources);
}

template <typename T>
void StateFactory::set_running_actions(T&& running_actions) 
{
  running_actions_ = std::forward<T>(running_actions);
}

}
