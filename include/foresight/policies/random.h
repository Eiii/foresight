#pragma once

#include "foresight/policy.h"

namespace fore {

class RandomPolicy : public Policy {
  //Constructors
  public:
    RandomPolicy(const Domain& domain);
    virtual ~RandomPolicy() = default;
    RandomPolicy(const RandomPolicy& rhs) = default;
    RandomPolicy& operator=(const RandomPolicy& rhs) = default;
    RandomPolicy(RandomPolicy&& rhs) = default;
    RandomPolicy& operator=(RandomPolicy&& rhs) = default;

  //Public functions
  public:
    Action::Ptr SelectAction(const State& state) override;
};

}
