#pragma once

#include "foresight/policies/uniform.h"
#include "foresight/actiontype.h"

namespace fore {

class UpfrontSmoothPolicy : public UniformPolicy {
  //Constructors
  public:
    UpfrontSmoothPolicy(const Domain& domain, ActionType::Id id1);
    virtual ~UpfrontSmoothPolicy() = default;
    UpfrontSmoothPolicy(const UpfrontSmoothPolicy& rhs) = default;
    UpfrontSmoothPolicy& operator=(const UpfrontSmoothPolicy& rhs) = default;
    UpfrontSmoothPolicy(UpfrontSmoothPolicy&& rhs) = default;
    UpfrontSmoothPolicy& operator=(UpfrontSmoothPolicy&& rhs) = default;

  //Public functions
  public:
    Ptr Clone() const override;

  //Protected functions
  protected:
    std::vector<int> CalcActionsPerStep(const Domain& domain) const override;
};

}
