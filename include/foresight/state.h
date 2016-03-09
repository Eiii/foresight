#pragma once

#include "foresight/action.h"
#include "foresight/resource.h"

#include <string>

namespace fore {

class State {
  //Constructors
  public:
    State(int timestep, Resource::Amount resources, 
          Action::List&& running_actions);
    virtual ~State() = default;
    State(const State& rhs);
    State& operator=(const State& rhs);
    State(State&& rhs) = default;
    State& operator=(State&& rhs) = default;

  //Public functions
  public:
    std::string Info() const;

  //Getters
  public:
    int time() const { return time_; }
    const Resource::Amount& resources() const { return resources_; }
    const Action::List& running_actions() const { return running_actions_; }

  private:
    //TODO: Time type?
    int time_;
    Resource::Amount resources_;
    Action::List running_actions_;
};

}
