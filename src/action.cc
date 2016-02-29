#include "foresight/action.h"

#include "foresight/actiontype.h"

namespace fore {

Action::Action(ActionType::Id type_id, int time_started) :
    type_id_(type_id), time_started_(time_started) {}

bool Action::operator==(const Action& rhs) const
{
  return (type_id_ == rhs.type_id_ &&
          time_started_ == rhs.time_started_);
}

}
