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
    State AdvanceTime(const State& state) const;
    State BeginAction(const State& state, const Action& action) const;
    bool IsDecisionPoint(const State& state) const;
    std::vector<Action::Ptr> LegalActions(const State& state) const;

  //Private functions
  private:
    bool IsActionFinished(const Action& action, const State& state) const;
    State EndAction(const State& state, const Action& action) const;

  //Member variables
  private:
    const Domain& domain_;
};

}
