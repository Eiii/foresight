#pragma once

#include "foresight/domain.h"

namespace fore {

class Simulator {
  //Constructors
  public:
    Simulator(const Domain& domain);
    virtual ~Simulator() = default;
    Simulator(const Simulator& rhs) = default;
    Simulator& operator=(const Simulator& rhs) = default;
    Simulator(Simulator&& rhs) = default;
    Simulator& operator=(Simulator&& rhs) = default;

  //Public functions
  public:
    State AdvanceTime(const State& state);
    State BeginAction(const State& state, const Action& action);

  //Member variables
  private:
    const Domain& domain_;
};

}
