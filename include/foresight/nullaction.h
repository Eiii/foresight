#pragma once

#include "foresight/action.h"

namespace fore {

//Fall back to defined type to avoid circular dependency
#define ACTIONTYPEID int

constexpr ACTIONTYPEID NullID = -1;
  
class NullAction : public Action {
  //Constructors
  public:
    NullAction(int time);
    virtual ~NullAction() = default;
    NullAction(const NullAction& rhs) = default;
    NullAction& operator=(const NullAction& rhs) = default;
    NullAction(NullAction&& rhs) = default;
    NullAction& operator=(NullAction&& rhs) = default;

  //Public functions
  public:
    virtual std::string Info(const Domain& domain) const override;
    virtual Ptr Clone() const override;
};

bool is_null_action(const Action& action);

}
