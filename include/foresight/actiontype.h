#pragma once

#include "foresight/duration.h"
#include "foresight/resource.h"

#include <map>
#include <string>

namespace fore {

class ActionType {
  //Type aliases
  public:
    using Id = int;
    using Map = std::map<Id, ActionType>;

  //Constructors 
  public:
    ActionType(int id, std::string name, int duration,
               Resource::Amount requires,
               Resource::Amount produces,
               Resource::Amount upkeep);
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
    Duration duration_;
    Resource::Amount requires_;
    Resource::Amount produces_;
    Resource::Amount upkeep_;
};

}
