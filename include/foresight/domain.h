#pragma once

#include "foresight/actiontype.h"
#include "foresight/resource.h"
#include "foresight/state.h"

#include <string>

namespace fore {

class Domain {
  public:
    Domain(ActionType::Map&& actions, Resource::Map&& resources, 
           int horizon, State init_state);
    virtual ~Domain() = default;
    //Forbid copying
    Domain(const Domain& other) = delete;
    Domain& operator=(const Domain& other) = delete;
    //Allow moving
    Domain(Domain&& rhs) = default;
    Domain& operator=(Domain& rhs) = default;

  //Public functions
  public:
    std::string info() const;

  //Getters
  public:
    const ActionType::Map& actions() const { return actions_; }
    const Resource::Map& resources() const { return resources_; }
    int horizon() const { return horizon_; }
    const State& initial_state() const { return initial_state_; }

  private:
    ActionType::Map actions_;
    Resource::Map resources_;
    int horizon_; //TODO: Timestep alias?
    const State initial_state_;
};

}
