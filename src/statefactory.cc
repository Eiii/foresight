#include "foresight/statefactory.h"

#include "foresight/actiontype.h"

using std::make_pair;

namespace fore {

StateFactory::StateFactory() :
    StateFactory(0) {}

StateFactory::StateFactory(const State& state) :
    time_(state.time()), 
    resources_(state.resources()), 
    running_actions_(copy_actions(state.running_actions())),
    observations_(state.observations()), 
    false_observations_(state.false_observations()) {}

StateFactory::StateFactory(int time) :
    time_(time), resources_(), running_actions_(),
    observations_(), false_observations_() {}

State StateFactory::Finish() const
{
  return State(time_, resources_, copy_actions(running_actions_), 
               observations_, false_observations_);
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
  running_actions_ = copy_actions(state.running_actions());
}

void StateFactory::SetResourceAmount(Resource::Id id, int amount)
{
  resources_[id] = amount;
}

void StateFactory::AddObservation(Model::Id id, Point p, double result)
{
  observations_[id].emplace_back(make_pair(p, result));
}

void StateFactory::AddFalseObservation(Model::Id id, Point p, double result)
{
  false_observations_[id].emplace_back(make_pair(p, result));
}

}
