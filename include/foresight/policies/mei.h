#pragma once

#include "foresight/policy.h"

namespace fore {

class MEIPolicy : public Policy {
  //Constructors
  public:
    MEIPolicy(const Domain& domain);
    virtual ~MEIPolicy() = default;
    MEIPolicy(const MEIPolicy& rhs) = default;
    MEIPolicy& operator=(const MEIPolicy& rhs) = default;
    MEIPolicy(MEIPolicy&& rhs) = default;
    MEIPolicy& operator=(MEIPolicy&& rhs) = default;

  //Public functions
  public:
    Action::Ptr SelectAction(const State& state) override;
    Ptr Clone() const override;
};

}
