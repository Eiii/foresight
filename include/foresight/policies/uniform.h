#pragma once

#include "foresight/actiontype.h"
#include "foresight/policy.h"

namespace fore {

class UniformPolicy : public Policy {
  //Constructors
  public:
    UniformPolicy(const Domain& domain, ActionType::Id action_id);
    virtual ~UniformPolicy() = default;
    UniformPolicy(const UniformPolicy& rhs) = default;
    UniformPolicy& operator=(const UniformPolicy& rhs) = default;
    UniformPolicy(UniformPolicy&& rhs) = default;
    UniformPolicy& operator=(UniformPolicy&& rhs) = default;

  //Public functions
  public:
    Action::Ptr SelectAction(const State& state) override;

  //Private functions
  private:
    int ActionsStarted(const State& state);
    int TotalRemaining(const State& state);

  //Private members
  private:
    ActionType::Id action_id_;

};

}
