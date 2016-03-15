#include "foresight/experimentaction.h"

#include "foresight/actiontype.h"

#include <sstream>

namespace fore {

ExperimentAction::ExperimentAction(ActionType::Id type_id, int time_started, 
                                   Point input_point) :
    Action(type_id, time_started), input_point_(input_point) {}

ExperimentAction::ExperimentAction(const Action& rhs, Point input_point) :
    Action(rhs), input_point_(input_point) {}

std::string ExperimentAction::Info(const Domain& domain) const
{
  std::stringstream ss;
  ss << Action::Info(domain) << " - EXP";
  return ss.str();
}

Action::Ptr ExperimentAction::Clone() const
{
  return std::make_unique<ExperimentAction>(*this);
}

}
