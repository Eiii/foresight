#pragma once

#include "foresight/policy.h"
#include "foresight/util/random.h"

namespace fore {

class RandomPolicy : public Policy {
  //Constructors
  public:
    RandomPolicy(const Domain& domain, int seed=1337);
    virtual ~RandomPolicy() = default;
    RandomPolicy(const RandomPolicy& rhs) = default;
    RandomPolicy& operator=(const RandomPolicy& rhs) = default;
    RandomPolicy(RandomPolicy&& rhs) = default;
    RandomPolicy& operator=(RandomPolicy&& rhs) = default;

  //Public functions
  public:
    Action::Ptr SelectAction(const State& state) override;
    Policy::Ptr Clone() const override;

  //Private member variables
  private:
    RandomEngine random_;
};

}
