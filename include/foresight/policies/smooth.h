#pragma once

#include "foresight/policies/uniform.h"
#include "foresight/actiontype.h"

namespace fore {

class SmoothPolicy : public UniformPolicy {
  //Constructors
  public:
    SmoothPolicy(const Domain& domain, ActionType::Id id1);
    virtual ~SmoothPolicy() = default;
    SmoothPolicy(const SmoothPolicy& rhs) = default;
    SmoothPolicy& operator=(const SmoothPolicy& rhs) = default;
    SmoothPolicy(SmoothPolicy&& rhs) = default;
    SmoothPolicy& operator=(SmoothPolicy&& rhs) = default;

  //Public functions
  public:
    Ptr Clone() const override;

  //Protected functions
  protected:
    std::vector<int> CalcActionsPerStep(const Domain& domain) const override;
};

}
