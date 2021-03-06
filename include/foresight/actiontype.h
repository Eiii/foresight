#pragma once

#include "foresight/duration.h"
#include "foresight/resource.h"
#include "foresight/state.h"

#include <map>
#include <string>
#include <vector>


namespace fore {

class RealWorld;
class StateFactory;

class ActionType {
  //Type aliases
  public:
    using Id = int;
    using Ptr = std::unique_ptr<ActionType>;
    using Map = std::map<Id, ActionType::Ptr>;

  //Constructors 
  public:
    ActionType(Id id, std::string name, Duration duration, bool cancelable,
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

  //Public functions
  public:
    bool CanStart(const State& state) const;
    virtual std::vector<Action::Ptr> 
      GenerateActions(const State& state, const Domain& domain) const;
    virtual State Start(const Action& action, const Domain& domain, 
                        const State& state) const;
    virtual void End(const Action& action, const Domain& domain,
                     const State& state, StateFactory* fact, 
                     const RealWorld& real) const;
    virtual State Cancel(const Action& target, const State& state) const;

  //Getters
  public:
    Id id() const { return id_; }
    const std::string& name() const { return name_; }
    bool cancelable() const { return cancelable_; }
    const Duration& duration() const { return duration_; }
    const Resource::Amount& requires() const { return requires_; }
    const Resource::Amount& produces() const { return produces_; }
    const Resource::Amount& upkeep() const { return upkeep_; }

  private:
    Id id_;
    std::string name_;
    Duration duration_;
    bool cancelable_;
    Resource::Amount requires_;
    Resource::Amount produces_;
    Resource::Amount upkeep_;
};

Action::List copy_actions(const Action::List& actions);

}
