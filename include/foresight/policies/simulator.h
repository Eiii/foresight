#pragma once

#include "foresight/policy.h"
#include "foresight/simulator.h"

namespace fore {

class SimulatorPolicy : public Policy {
  //Constructors
  public:
    SimulatorPolicy(const Domain& domain) :
      Policy(domain), simulator_(domain) {}
    virtual ~SimulatorPolicy() = default;
    SimulatorPolicy(const SimulatorPolicy& rhs) = default;
    SimulatorPolicy& operator=(const SimulatorPolicy& rhs) = default;
    SimulatorPolicy(SimulatorPolicy&& rhs) = default;
    SimulatorPolicy& operator=(SimulatorPolicy&& rhs) = default;

  //Public functions
  public:
    virtual Action::Ptr SelectAction(const State& state) = 0;

  //Protected members
  protected:
    Simulator simulator_;
};

}
