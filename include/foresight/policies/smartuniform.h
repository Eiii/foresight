#pragma once

#include "foresight/actiontype.h"
#include "foresight/policies/uniform.h"

namespace fore {

class SmartUniformPolicy : public Policy {
  //Constructors
  public:
    SmartUniformPolicy(const Domain& domain, 
        ActionType::Id id1, ActionType::Id id2);
    virtual ~SmartUniformPolicy() = default;
    SmartUniformPolicy(const SmartUniformPolicy& rhs);
    SmartUniformPolicy& operator=(const SmartUniformPolicy& rhs);
    SmartUniformPolicy(SmartUniformPolicy&& rhs) = default;
    SmartUniformPolicy& operator=(SmartUniformPolicy&& rhs) = default;

  //Public functions
  public:
    Action::Ptr SelectAction(const State& state) override;
    Ptr Clone() const override;

  private:
    Policy::Ptr policy1_;
    Policy::Ptr policy2_;
    bool switched_;
};

}
