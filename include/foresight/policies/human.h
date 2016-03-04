#pragma once

#include "foresight/policy.h"
#include "foresight/simulator.h"

namespace fore {

class HumanPolicy : public Policy {
  //Constructors
  public:
    HumanPolicy(const Domain& domain);
    virtual ~HumanPolicy() = default;
    HumanPolicy(const HumanPolicy& rhs) = default;
    HumanPolicy& operator=(const HumanPolicy& rhs) = default;
    HumanPolicy(HumanPolicy&& rhs) = default;
    HumanPolicy& operator=(HumanPolicy&& rhs) = default;

  //Public functions
  public:
    Action::Ptr SelectAction(const State& state) override;

  //Private members
  private:
    Simulator simulator_;
};

}
