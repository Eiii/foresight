#include "foresight/state.h"

#include <sstream>

namespace fore {

State::State(int timestep, Resource::Amount resources) :
    timestep_(timestep), resources_(resources) {}

State::State(const State& rhs) :
    timestep_(), resources_() 
{ 
  timestep_ = rhs.timestep_;
  resources_ = rhs.resources_;
};

std::string State::info() const
{
  std::stringstream ss;
  ss << "Time: " << timestep_ << std::endl;
  ss << "Resources: " << std::endl;
  for (const auto& key : resources_) {
    ss << "\t" << key.first << ": " << key.second; 
  }
  ss << "Running actions: " << std::endl;
  ss << "\t(TODO)" << std::endl;

  //TODO: Observations?
  return ss.str();
}

}
