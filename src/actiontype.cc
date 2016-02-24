#include "foresight/actiontype.h"

using std::move;

namespace fore {

ActionType::ActionType(int id, std::string name, int duration,
                       Resource::Amount requires,
                       Resource::Amount produces,
                       Resource::Amount upkeep) :
    id_(id), name_(name), duration_(duration), requires_(move(requires)),
    produces_(move(produces)), upkeep_(move(upkeep)) {}

}
