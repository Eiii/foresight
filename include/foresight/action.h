#pragma once

#include "foresight/actiontype.h"

#include <vector>

namespace fore {

class Action {
  //Type aliases
  public:
    using List = std::vector<Action>;

  //Constructors
  public:
    Action(ActionType::Id type_id, int time_started);
    virtual ~Action() = default;
    Action(const Action& rhs) = default;
    Action& operator=(const Action& rhs) = default;
    Action(Action&& rhs) = default;
    Action& operator=(Action&& rhs) = default;

  //Getters/setters
  public:
    ActionType::Id type_id() const { return type_id_; }
    int time_started() const { return time_started_; }

  //Member variables
  private:
    ActionType::Id type_id_;
    int time_started_;
};

}
