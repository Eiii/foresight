#include "foresight/state.h"

#include <sstream>

static void show_resource_amounts(std::stringstream* ss, 
                                 fore::Resource::Amount amt);
static void show_running_actions(std::stringstream* ss, 
                                 fore::Action::List running);

namespace fore {

State::State(int time, Resource::Amount resources, 
             Action::List running_actions) :
    time_(time), resources_(resources), 
    running_actions_(running_actions) {}

State::State(const State& rhs) :
    time_(rhs.time_), 
    resources_(rhs.resources_),
    running_actions_(rhs.running_actions_) {}

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

void show_running_actions(std::stringstream* ss, fore::Action::List running)
{
  if (running.size() == 0) {
    *ss << "\t(None)" << std::endl;
  }
  for (const auto& action : running) {
    *ss << "\t" << action.type_id() << " - " << action.time_started();
    *ss << std::endl;
  }
}
