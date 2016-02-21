#pragma once

#include "foresight/actiontype.h"
#include "foresight/resourcetype.h"

namespace fore {

class Domain {
  public:
    Domain(ActionType::Map&& actions, ResourceType::Map&& resources, 
           int horizon);
    virtual ~Domain() = default;
    //Forbid copying
    Domain(const Domain& other) = delete;
    Domain& operator=(const Domain& other) = delete;
    //Allow moving
    Domain(Domain&& rhs) = default;
    Domain& operator=(Domain& rhs) = default;

  //Getters
  public:
    const ActionType::Map& actions() const { return actions_; }
    const ResourceType::Map& resources() const { return resources_; }
    int horizon() const { return horizon_; }

  private:
    ActionType::Map actions_;
    ResourceType::Map resources_;
    int horizon_; //TODO: Timestep alias?
};

}
