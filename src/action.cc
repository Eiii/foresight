#include "foresight/action.h"

namespace fore {

Action::Action(ActionType::Id type_id, int time_started) :
    type_id_(type_id), time_started_(time_started) {}

}
