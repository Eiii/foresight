#pragma once

#include "foresight/policies/simulator.h"

namespace fore {

class HumanPolicy : public SimulatorPolicy {
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
};

}
