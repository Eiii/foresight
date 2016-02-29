#pragma once

#include <vector>

namespace fore {

namespace {
  //Copy the type of ActionType::Id to avoid circular definition
  //TODO: This is dumb
  using ActionTypeId = int;
}

class Action {
  //Type aliases
  public:
    using List = std::vector<Action>;

  //Constructors
  public:
    Action(ActionTypeId type_id, int time_started);
    virtual ~Action() = default;
    Action(const Action& rhs) = default;
    Action& operator=(const Action& rhs) = default;
    Action(Action&& rhs) = default;
    Action& operator=(Action&& rhs) = default;

  public:
    bool operator==(const Action& rhs) const;

  //Getters/setters
  public:
    ActionTypeId type_id() const { return type_id_; }
    int time_started() const { return time_started_; }

  //Member variables
  private:
    ActionTypeId type_id_;
    int time_started_;
};

}
