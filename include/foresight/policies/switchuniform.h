#pragma once

#include "foresight/actiontype.h"
#include "foresight/policies/uniform.h"

namespace fore {

class SwitchUniformPolicy : public Policy {
  //Constructors
  public:
    SwitchUniformPolicy(const Domain& domain, 
        ActionType::Id id1, ActionType::Id id2, int time);
    virtual ~SwitchUniformPolicy() = default;
    SwitchUniformPolicy(const SwitchUniformPolicy& rhs) = default;
    SwitchUniformPolicy& operator=(const SwitchUniformPolicy& rhs) = default;
    SwitchUniformPolicy(SwitchUniformPolicy&& rhs) = default;
    SwitchUniformPolicy& operator=(SwitchUniformPolicy&& rhs) = default;

  //Public functions
  public:
    Action::Ptr SelectAction(const State& state) override;

  private:
    Policy::Ptr policy1_;
    Policy::Ptr policy2_;
    int switch_time_;
};

}
