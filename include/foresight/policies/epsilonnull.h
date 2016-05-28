#pragma once

#include "foresight/policy.h"
#include "foresight/util/random.h"

namespace fore {

class EpsilonNullPolicy : public Policy {
  //Constructors
  public:
    EpsilonNullPolicy(const Domain& domain, double epsilon, int seed=1337);
    virtual ~EpsilonNullPolicy() = default;
    EpsilonNullPolicy(const EpsilonNullPolicy& rhs) = default;
    EpsilonNullPolicy& operator=(const EpsilonNullPolicy& rhs) = default;
    EpsilonNullPolicy(EpsilonNullPolicy&& rhs) = default;
    EpsilonNullPolicy& operator=(EpsilonNullPolicy&& rhs) = default;

  //Public functions
  public:
    Action::Ptr SelectAction(const State& state) override;
    Ptr Clone() const override;

  //Private member variables
  private:
    RandomEngine random_;
    double epsilon_;
};

}
