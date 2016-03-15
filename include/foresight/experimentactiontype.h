#pragma once

#include "foresight/actiontype.h"
#include "foresight/model.h"

namespace fore {

class ExperimentActionType : public ActionType {
  //Type aliases
  public:
    using Ptr = std::unique_ptr<ExperimentActionType>;

  //Constructors
  public:
    ExperimentActionType(ActionType::Id id, std::string name,
                         Duration duration, bool cancelable,
                         Resource::Amount requires,
                         Resource::Amount produces,
                         Resource::Amount upkeep,
                         Model::Id model_id);
    virtual ~ExperimentActionType() = default;
    //Forbid copying
    ExperimentActionType(const ExperimentActionType& rhs) = delete;
    ExperimentActionType& operator=(const ExperimentActionType& rhs) = delete;
    //Allow moving
    ExperimentActionType(ExperimentActionType&& rhs) = default;
    ExperimentActionType& operator=(ExperimentActionType&& rhs) = default;

  //Public functions
  public:
    virtual std::vector<Action::Ptr> 
      GenerateActions(const State& state, const Domain& domain) const override;
    virtual State 
      Start(const Action& action, const Domain& domain, 
            const State& state) const override;
    virtual void 
      End(const Action& action, const Domain& domain,
          const State& state, StateFactory* fact) const override;
    virtual State 
      Cancel(const Action& target, const State& state) const override;

  //Member variables
  private:
    Model::Id model_id_;

};

}
