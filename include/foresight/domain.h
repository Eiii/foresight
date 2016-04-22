#pragma once

#include "foresight/actiontype.h"
#include "foresight/model.h"
#include "foresight/resource.h"
#include "foresight/state.h"

#include <string>

namespace fore {

class Domain {
  public:
    Domain(ActionType::Map&& actions, Resource::Map&& resources, 
           Model::Map&& models, int horizon, State init_state);
    virtual ~Domain() = default;
    //Forbid copying
    Domain(const Domain& other) = delete;
    Domain& operator=(const Domain& other) = delete;
    //Allow moving
    Domain(Domain&& rhs) = default;
    Domain& operator=(Domain& rhs) = default;

  //Public functions
  public:
    std::string Info() const;

  //Helper Getters
  public:
    const ActionType& action_type(ActionType::Id id) const;
    const Resource& resource(Resource::Id id) const;
    const Model& model(Model::Id id) const;

  //Getters
  public:
    const ActionType::Map& action_types() const { return action_types_; }
    const Resource::Map& resources() const { return resources_; }
    const Model::Map& models() const { return models_; }
    int horizon() const { return horizon_; }
    const State& initial_state() const { return initial_state_; }

  private:
    ActionType::Map action_types_;
    Resource::Map resources_;
    Model::Map models_;
    int horizon_; //TODO: Timestep alias?
    const State initial_state_;
};

}
