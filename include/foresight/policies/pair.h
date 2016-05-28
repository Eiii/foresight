#pragma once

#include "foresight/policy.h"

namespace fore {

class PairPolicy : public Policy {
  //Constructors
  public:
    PairPolicy(const Domain& domain, Policy::Ptr&& exp, Policy::Ptr&& res);
    virtual ~PairPolicy() = default;
    PairPolicy(const PairPolicy& rhs);
    PairPolicy& operator=(const PairPolicy& rhs);
    PairPolicy(PairPolicy&& rhs) = default;
    PairPolicy& operator=(PairPolicy&& rhs) = default;

  //Public functions
  public:
    Action::Ptr SelectAction(const State& state) override;
    Ptr Clone() const override;

  //Private member variables
  private:
    Policy::Ptr exp_policy_;
    Policy::Ptr res_policy_;
};

}
