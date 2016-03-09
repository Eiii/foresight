#include "foresight/experimentactiontypefactory.h"

namespace fore {

ExperimentActionTypeFactory::ExperimentActionTypeFactory(
    int id, std::string name, Duration duration, Model::Id model_id
  ) :
    ActionTypeFactory(id, name, duration), model_id_(model_id) {};

ActionType::Ptr ExperimentActionTypeFactory::Finish() const
{
  return std::make_unique<ExperimentActionType>(
      id_, name_, duration_, cancelable_, 
      requires_, produces_, upkeep_, model_id_ 
    );
}

}
