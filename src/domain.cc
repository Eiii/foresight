#include "foresight/domain.h"

#include <sstream>

using std::move;
using std::string;
using std::endl;

namespace fore {

Domain::Domain(ActionType::Map&& actions, Resource::Map&& resources, 
               int horizon, State init_state) :
    actions_(move(actions)),
    resources_(move(resources)),
    horizon_(horizon),
    initial_state_(init_state) {}

string Domain::info() const
{
  std::stringstream ss; 
  ss << "Resources:" << endl;
  for (const auto& key : resources_) {
    const auto& res = key.second;
    ss << "\t" << res.id() << " / " << res.name() << endl;
  }
  ss << "Actions:" << endl;
  for (const auto& key : actions_) {
    const auto& action = key.second;
    ss << "\t" << action.id() << " / " << action.name();
  }
  return ss.str();
}

}
