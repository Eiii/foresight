#pragma once

#include "foresight/action.h"
#include "foresight/resource.h"

#include <string>

namespace fore {

class State {
  //Constructors
  public:
    State(int timestep, Resource::Amount resources, 
          Action::List running_actions);
    virtual ~State() = default;
    State(const State& rhs);
    State& operator=(const State& rhs) = default;
    State(State&& rhs) = default;
    State& operator=(State&& rhs) = default;

  //Public functions
  public:
    std::string info() const;

  //Getters
  public:
    int timestep() const { return timestep_; };
    Resource::Amount resources() const { return resources_; };

  private:
    //TODO: Time type?
    int timestep_;
    Resource::Amount resources_;
    Action::List running_actions_;
};

}
