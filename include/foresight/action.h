#pragma once

#include <memory>
#include <vector>

namespace fore {

//Fall back to defined type to avoid circular dependency
#define ACTIONTYPEID int

//Forward declared classes
class Domain;

class Action {
  //Type aliases
  public:
    using Ptr = std::unique_ptr<Action>;
    using List = std::vector<Action>;

  //Constructors
  public:
    Action(ACTIONTYPEID type_id, int time_started);
    virtual ~Action() = default;
    Action(const Action& rhs) = default;
    Action& operator=(const Action& rhs) = default;
    Action(Action&& rhs) = default;
    Action& operator=(Action&& rhs) = default;

  //Public functions
  public:
    virtual std::string Info(const Domain& domain) const;

  //Operators
  public:
    bool operator==(const Action& rhs) const;

  //Getters/setters
  public:
    ACTIONTYPEID type_id() const { return type_id_; }
    int time_started() const { return time_started_; }

  //Member variables
  private:
    ACTIONTYPEID type_id_;
    int time_started_;
};

#undef ACTIONTYPEID

}
