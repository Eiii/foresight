#include "foresight/domain.h"

using std::move;

namespace fore {

Domain::Domain(ActionType::Map&& actions, ResourceType::Map&& resources, 
               int horizon) :
    actions_(move(actions)),
    resources_(move(resources)),
    horizon_(horizon) {}

}
