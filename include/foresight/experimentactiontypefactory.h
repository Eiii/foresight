#pragma once

#include "foresight/actiontypefactory.h"
#include "foresight/experimentactiontype.h"
#include "foresight/model.h"

namespace fore {

class ExperimentActionTypeFactory : public ActionTypeFactory {
  //Constructors
  public:
    ExperimentActionTypeFactory(int id, std::string name, Duration duration, 
                                Model::Id model_id);
    virtual ~ExperimentActionTypeFactory() = default;
    ExperimentActionTypeFactory(const ExperimentActionTypeFactory& rhs) 
      = default;
    ExperimentActionTypeFactory& operator=(
        const ExperimentActionTypeFactory& rhs
      ) = default;
    ExperimentActionTypeFactory(ExperimentActionTypeFactory&& rhs) = default;
    ExperimentActionTypeFactory& operator=(ExperimentActionTypeFactory&& rhs) 
      = default;

  //Public functions
  public:
    ActionType::Ptr Finish() const override;

  //Setters
  public:
    void set_model_id(Model::Id id) { model_id_ = id; }

  //Member variables
  protected:
    Model::Id model_id_;
};

}
