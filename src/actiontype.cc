#include "foresight/actiontype.h"

namespace fore {

ActionType::ActionType(Id id, std::string name, Duration duration,
                       Resource::Amount requires,
                       Resource::Amount produces,
                       Resource::Amount upkeep) :
    id_(id), name_(name), duration_(duration), requires_(requires),
    produces_(produces), upkeep_(upkeep) {}

}
