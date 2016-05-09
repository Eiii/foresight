#include "foresight/domainfactory.h"

using std::move;

namespace fore {

//TODO: Should state me moved into initial_state?
DomainFactory::DomainFactory(int horizon, State state) :
    action_types_(), resources_(), models_(), 
    horizon_(horizon), has_null_action_(false), initial_state_(state) {}

Domain DomainFactory::FinishAndReset() 
{
  Domain d(move(action_types_), move(resources_), move(models_), 
           horizon_, has_null_action_, initial_state_);
  Reset(horizon_, initial_state_);
  return d;
}

void DomainFactory::Reset(int horizon, State state)
{
  action_types_.clear();
  resources_.clear();
  models_.clear();
  horizon_ = horizon;
  has_null_action_ = false;
  initial_state_ = state; //TODO: Move this?
}

void DomainFactory::AddActionType(ActionType::Ptr&& action_ptr)
{
  auto id = action_ptr->id();
  action_types_.emplace(id, move(action_ptr));
}

void DomainFactory::AddModel(Model&& model)
{
  auto id = model.id();
  models_.emplace(id, std::move(model));
}

}
