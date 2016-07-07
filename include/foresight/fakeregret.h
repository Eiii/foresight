#pragma once

#include "foresight/regret.h"
#include "foresight/domain.h"
#include "foresight/state.h"

namespace fore {

class FakeRegret : public Regret {
  //Constructors
  public:
    FakeRegret(const Domain& domain, const State& state);
    ~FakeRegret() = default;
    FakeRegret(const FakeRegret&) = delete;
    FakeRegret& operator=(const FakeRegret&) = delete;
    FakeRegret(FakeRegret&&) = delete;
    FakeRegret& operator=(FakeRegret&&) = delete;

  protected:
    void CalculateMinimumWithState(const State& state);
};

}
