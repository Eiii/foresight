#pragma once

#include "foresight/resource.h"

#include <string>

namespace fore {

class State {
  //Constructors
  public:
    State(int timestep, Resource::Amount resources);
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
    //TODO: Currently running actions
};

}
