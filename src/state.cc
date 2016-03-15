#include "foresight/state.h"
#include "foresight/actiontype.h"

#include <sstream>

static void show_resource_amounts(std::stringstream* ss, 
                                 fore::Resource::Amount amt);
static void show_running_actions(std::stringstream* ss, 
                                 const fore::Action::List& running);

namespace fore {

State::State(int time, Resource::Amount resources, 
             Action::List&& running_actions,
             Model::ObsMap obs, Model::ObsMap false_obs) :
    time_(time), resources_(resources), 
    running_actions_(std::move(running_actions)),
    observations_(obs), false_observations_(false_obs) {}

State::State(const State& rhs) :
    time_(rhs.time_), 
    resources_(rhs.resources_),
    running_actions_(),
    observations_(rhs.observations_),
    false_observations_(rhs.false_observations_)
{
  running_actions_ = copy_actions(rhs.running_actions_);
}

State& State::operator=(const State& rhs)
{
  State s(rhs);
  std::swap(*this, s);
  return *this;
}

std::string State::Info() const
{
  std::stringstream ss;
  ss << "Time: " << time_ << std::endl;
  ss << "Resources: " << std::endl;
  show_resource_amounts(&ss, resources_);
  ss << "Running actions: " << std::endl;
  show_running_actions(&ss, running_actions_);
  //TODO: Observations?
  return ss.str();
}

}

void show_resource_amounts(std::stringstream* ss, fore::Resource::Amount amt)
{
  if (amt.size() == 0) {
    *ss << "\t(None)" << std::endl;
  }
  for (const auto& key : amt) {
    *ss << "\t" << key.first << ": " << key.second << std::endl; 
  }
}

void show_running_actions(std::stringstream* ss, 
                          const fore::Action::List& running)
{
  if (running.size() == 0) {
    *ss << "\t(None)" << std::endl;
  }
  for (const auto& action : running) {
    *ss << "\t" << action->type_id() << " - " << action->time_started();
    *ss << std::endl;
  }
}
