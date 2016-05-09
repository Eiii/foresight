#include "foresight/nullaction.h"

#include "foresight/actiontype.h"
#include "foresight/domain.h"

namespace fore {
 
NullAction::NullAction(int time) :
    Action(NullID, time) {}

std::string NullAction::Info(const Domain& domain) const
{
  (void)domain;
  return std::string("Null action");
}

Action::Ptr NullAction::Clone() const
{
  return std::make_unique<NullAction>(*this);
}

bool is_null_action(const Action& action)
{
  return typeid(action) == typeid(NullAction);
}

}
