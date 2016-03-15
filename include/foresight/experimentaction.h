#pragma once

#include "foresight/action.h"
#include "foresight/types.h"

namespace fore {

//Fall back to defined type to avoid circular dependency
#define ACTIONTYPEID int

class ExperimentAction : public Action{
  //Constructors
  public:
    ExperimentAction(ACTIONTYPEID type_id, int time_started, 
                     Point input_point);
    virtual ~ExperimentAction() = default;
    ExperimentAction(const ExperimentAction& rhs) = default;
    ExperimentAction& operator=(const ExperimentAction& rhs) = default;
    ExperimentAction(ExperimentAction&& rhs) = default;
    ExperimentAction& operator=(ExperimentAction&& rhs) = default;

  //Alternative constructors
  public:
    ExperimentAction(const Action& rhs, Point input_point);

  //Public functions
  public:
    virtual std::string Info(const Domain& domain) const override;
    virtual Ptr Clone() const override;

  //Operators
  public:
    bool operator==(const ExperimentAction& rhs) const;

  //Member variables
  private:
    Point input_point_;
};

#undef ACTIONTYPEID

}
