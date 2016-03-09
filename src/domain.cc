#include "foresight/domain.h"

#include <sstream>

using std::move;
using std::string;
using std::endl;

namespace fore {

Domain::Domain(ActionType::Map&& action_types, Resource::Map&& resources, 
               int horizon, State init_state) :
    action_types_(move(action_types)),
    resources_(move(resources)),
    horizon_(horizon),
    initial_state_(init_state) {}

string Domain::Info() const
{
  std::stringstream ss; 
  ss << "Resources:" << endl;
  for (const auto& key : resources_) {
    const auto& res = key.second;
    ss << "\t" << res.id() << " / " << res.name() << endl;
  }
  ss << "Actions:" << endl;
  for (const auto& key : action_types_) {
    const auto& action = key.second;
    ss << "\t" << action->id() << " / " << action->name();
  }
  return ss.str();
}

const ActionType& Domain::action_type(ActionType::Id id) const
{
  return *action_types_.at(id);
}

const Resource& Domain::resource(Resource::Id id) const 
{
  return resources_.at(id);
}

}
