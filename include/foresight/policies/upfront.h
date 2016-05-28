#pragma once

#include "foresight/policy.h"
#include "foresight/actiontype.h"

namespace fore {

class UpfrontPolicy : public Policy {
  //Constructors
  public:
    UpfrontPolicy(const Domain& domain, ActionType::Id id1, ActionType::Id id2);
    virtual ~UpfrontPolicy() = default;
    UpfrontPolicy(const UpfrontPolicy& rhs);
    UpfrontPolicy& operator=(const UpfrontPolicy& rhs);
    UpfrontPolicy(UpfrontPolicy&& rhs) = default;
    UpfrontPolicy& operator=(UpfrontPolicy&& rhs) = default;

  //Public functions
  public:
    Action::Ptr SelectAction(const State& state) override;
    Ptr Clone() const override;

  //Private functions
  private:
    int CalculateFirstBatchSize(const State& state) const;
    int ActionsStarted(const State& state) const;

  private:
    ActionType::Id first_id_;
    ActionType::Id seq_id_;
    Policy::Ptr uniform_policy_;
};

}
