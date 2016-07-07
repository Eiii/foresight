#pragma once

#include "foresight/policies/uniform.h"
#include "foresight/actiontype.h"

namespace fore {

class UpfrontBadPolicy : public UniformPolicy {
  //Constructors
  public:
    UpfrontBadPolicy(const Domain& domain, ActionType::Id id1);
    virtual ~UpfrontBadPolicy() = default;
    UpfrontBadPolicy(const UpfrontBadPolicy& rhs) = default;
    UpfrontBadPolicy& operator=(const UpfrontBadPolicy& rhs) = default;
    UpfrontBadPolicy(UpfrontBadPolicy&& rhs) = default;
    UpfrontBadPolicy& operator=(UpfrontBadPolicy&& rhs) = default;

  //Public functions
  public:
    Ptr Clone() const override;

  //Protected functions
  protected:
    std::vector<int> CalcActionsPerStep(const Domain& domain) const override;
};

}
