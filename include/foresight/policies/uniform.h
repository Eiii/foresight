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
    Ptr Clone() const override;

  //Protected functions
  protected:
    virtual std::vector<int> CalcActionsPerStep(const Domain& domain) const;

  //Private functions
  private:
    int ActionsStarted(const State& state) const;

  //Private members
  private:
    ActionType::Id action_id_;

  //Protected members
  protected:
    std::vector<int> actions_per_step_;

};

}
