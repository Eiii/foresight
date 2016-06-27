#pragma once

#include "foresight/policies/uniform.h"
#include "foresight/actiontype.h"

namespace fore {

class UpfrontPolicy : public UniformPolicy {
  //Constructors
  public:
    UpfrontPolicy(const Domain& domain, ActionType::Id id1);
    virtual ~UpfrontPolicy() = default;
    UpfrontPolicy(const UpfrontPolicy& rhs) = default;
    UpfrontPolicy& operator=(const UpfrontPolicy& rhs) = default;
    UpfrontPolicy(UpfrontPolicy&& rhs) = default;
    UpfrontPolicy& operator=(UpfrontPolicy&& rhs) = default;

  //Public functions
  public:
    Ptr Clone() const override;

  //Protected functions
  protected:
    std::vector<int> CalcActionsPerStep(const Domain& domain) const override;
};

}
