#pragma once

#include "foresight/action.h"

namespace fore {

//Fall back to defined type to avoid circular dependency
#define ACTIONTYPEID int
  
class CancelAction : public Action {
  //Constructors
  public:
    CancelAction(int time, const Action& target);
    virtual ~CancelAction() = default;
    CancelAction(const CancelAction& rhs) = default;
    CancelAction& operator=(const CancelAction& rhs) = default;
    CancelAction(CancelAction&& rhs) = default;
    CancelAction& operator=(CancelAction&& rhs) = default;

  //Public functions
  public:
    virtual std::string Info(const Domain& domain) const override;
    virtual Ptr Clone() const override;

  //Operators
  public:
    bool operator==(const CancelAction& rhs) const;

  //Getters
  public:
    const Action& target() const { return target_; }

  //Member variables
  private:
    const Action& target_;
};

bool is_cancel_action(const Action& action);

}
