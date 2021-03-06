#include "foresight/actiontypefactory.h"

namespace fore {

ActionTypeFactory::ActionTypeFactory(int id, std::string name, 
                                     Duration duration) :
    id_(id), name_(name), duration_(duration), cancelable_(false),
    requires_(), produces_(), upkeep_() {}

ActionType::Ptr ActionTypeFactory::Finish() const
{
  return std::make_unique<ActionType>(id_, name_, duration_, cancelable_, 
                                      requires_, produces_, upkeep_);
}

void ActionTypeFactory::Reset(ActionType::Id id, std::string name, 
                              Duration duration)
{
  id_ = id;
  name_ = name;
  duration_ = duration;
  cancelable_ = false;
  requires_.clear();
  produces_.clear();
  upkeep_.clear();
}

void ActionTypeFactory::SetResourceRequirement(Resource::Id id, int amount)
{
  requires_[id] = amount;
}

void ActionTypeFactory::SetResourceProduction(Resource::Id id, int amount)
{
  produces_[id] = amount;
}

void ActionTypeFactory::SetResourceUpkeep(Resource::Id id, int amount)
{
  upkeep_[id] = amount;
}

}
