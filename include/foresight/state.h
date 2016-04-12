#pragma once

#include "foresight/action.h"
#include "foresight/model.h"
#include "foresight/resource.h"

#include <string>

namespace fore {

class State {
  //Constructors
  public:
    State(int timestep, Resource::Amount resources, 
          Action::List&& running_actions, 
          Model::ObsMap obs, Model::ObsMap false_obs);
    virtual ~State() = default;
    State(const State& rhs);
    State& operator=(const State& rhs);
    State(State&& rhs) = default;
    State& operator=(State&& rhs) = default;

  //Public functions
  public:
    std::string Info(const Domain& domain) const;

  //Getters
  public:
    int time() const { return time_; }
    const Resource::Amount& resources() const { return resources_; }
    const Action::List& running_actions() const { return running_actions_; }
    const Model::ObsMap& observations() const { return observations_; }
    const Model::ObsMap& false_observations() const 
      { return false_observations_; }

  private:
    //TODO: Time type?
    int time_;
    Resource::Amount resources_;
    Action::List running_actions_;
    Model::ObsMap observations_;
    Model::ObsMap false_observations_;
};

}
