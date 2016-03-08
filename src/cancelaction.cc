#include "foresight/cancelaction.h"

#include "foresight/actiontype.h"
#include "foresight/domain.h"

#include <sstream>

namespace fore {

CancelAction::CancelAction(int time, const Action& target) :
    Action(target.type_id(), time), target_(target) {}

std::string CancelAction::Info(const Domain& domain) const
{
  std::stringstream ss;
  ss << "Cancel '" << target_.Info(domain) << "'";
  return ss.str();
}

bool CancelAction::operator==(const CancelAction& rhs) const
{
  return (Action::operator==(rhs)) && (target_ == rhs.target_);
}

bool is_cancel_action(const Action& action)
{
  return typeid(action) == typeid(CancelAction);
}

}
