#pragma once

#include "foresight/domain.h"
#include "foresight/state.h"

namespace fore {

class Regret {
  //Constructors
  public:
    Regret(const Domain& domain);
    ~Regret() = default;
    Regret(const Regret&) = delete;
    Regret& operator=(const Regret&) = delete;
    Regret(Regret&&) = delete;
    Regret& operator=(Regret&&) = delete;

  public:
    double CalculateRegret(const State& state);

  protected:
    void CalculateMinimum();

  private:
    const Domain& domain_;
    double actual_min_;
};

}
