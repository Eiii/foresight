#pragma once

#include "foresight/policy.h"
#include "foresight/actiontype.h"

namespace fore {

class Upfront : public Policy {
  //Constructors
  public:
    Upfront(const Domain& domain, ActionType::Id id1, ActionType::Id id2);
    virtual ~Upfront() = default;
    Upfront(const Upfront& rhs) = default;
    Upfront& operator=(const Upfront& rhs) = default;
    Upfront(Upfront&& rhs) = default;
    Upfront& operator=(Upfront&& rhs) = default;

  //Public functions
  public:
    Action::Ptr SelectAction(const State& state) override;

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
