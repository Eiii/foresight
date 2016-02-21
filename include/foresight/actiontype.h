#pragma once

#include <map>
#include <string>

namespace fore {

class ActionType {
  public:
    using Id = int;
    using Map = std::map<Id, ActionType>;

  public:
    ActionType(int id, std::string name);
    virtual ~ActionType() = default;
    //Forbid copying
    ActionType(const ActionType& rhs) = delete;
    ActionType& operator=(const ActionType& rhs) = delete;
    //Allow moving
    ActionType(ActionType&& rhs) = default;
    ActionType& operator=(ActionType&& rhs) = default;

  //Getters
  public:
    Id id() const { return id_; }
    const std::string& name() const { return name_; }

  private:
    Id id_;
    std::string name_;
};

}
