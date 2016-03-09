#include "foresight/action.h"

#include "foresight/actiontype.h"
#include "foresight/domain.h"

#include <sstream>

namespace fore {

Action::Action(ActionType::Id type_id, int time_started) :
    type_id_(type_id), time_started_(time_started) {}

std::string Action::Info(const Domain& domain) const
{
  std::stringstream ss;
  ss << domain.action_type(type_id_).name();
  return ss.str();
}

Action::Ptr Action::Clone() const
{
  return std::make_unique<Action>(*this);
}

bool Action::operator==(const Action& rhs) const
{
  return (type_id_ == rhs.type_id_ &&
          time_started_ == rhs.time_started_);
}

}
