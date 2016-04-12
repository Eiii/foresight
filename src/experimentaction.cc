#include "foresight/experimentaction.h"

#include "foresight/actiontype.h"

#include <sstream>

namespace fore {

ExperimentAction::ExperimentAction(ActionType::Id type_id, int time_started, 
                                   Point input_point, double false_res) :
    Action(type_id, time_started), input_point_(input_point), 
    false_result_(false_res) {}

ExperimentAction::ExperimentAction(const Action& rhs, Point input_point, 
                                   double false_result) :
    Action(rhs), input_point_(input_point), false_result_(false_result) {}

std::string ExperimentAction::Info(const Domain& domain) const
{
  std::stringstream ss;
  ss << Action::Info(domain) << ": " << input_point_ << ", " << false_result_;
  return ss.str();
}

Action::Ptr ExperimentAction::Clone() const
{
  return std::make_unique<ExperimentAction>(*this);
}

}
