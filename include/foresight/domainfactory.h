#pragma once

#include "foresight/domain.h"

namespace fore {

class DomainFactory {
  //Constructors
  public:
    DomainFactory(int horizon, State state);
    virtual ~DomainFactory() = default;
    //Forbid copying
    DomainFactory(const DomainFactory& rhs) = delete ;
    DomainFactory& operator=(const DomainFactory& rhs) = delete;
    //Allow moving
    DomainFactory(DomainFactory&& rhs) = default;
    DomainFactory& operator=(DomainFactory&& rhs) = default;

  //Public functions
  public:
    Domain FinishAndReset();
    void Reset(int horizon, State state);
    template<typename... Args>
    void AddActionType(Args&&... args);
    template<typename... Args>
    void AddResource(Args&&... args);

  //Template setters
  public:
    void set_horizon(int horizon) { horizon_ = horizon; }
    template<typename T>
    void set_action_types(T&& action_types);
    template<typename T>
    void set_resources(T&& resources);
    template<typename T>
    void set_initial_state(T&& state);

  //Member variables
  private:
    ActionType::Map action_types_;
    Resource::Map resources_;
    int horizon_;
    State initial_state_;
};

//Template implementations
template<typename... Args>
void DomainFactory::AddActionType(Args&&... args)
{
  ActionType action_type(std::forward<Args>(args)...);
  auto id = action_type.id();
  action_types_.emplace(id, std::move(action_type));
}

template<typename... Args>
void DomainFactory::AddResource(Args&&... args)
{
  Resource resource(std::forward<Args>(args)...);
  auto id = resource.id();
  resources_.emplace(id, std::move(resource));
}

template<typename T>
void DomainFactory::set_action_types(T&& action_types)
{
  action_types_ = std::forward<T>(action_types);
}

template<typename T>
void DomainFactory::set_resources(T&& resources)
{
  resources_ = std::forward<T>(resources);
}

template<typename T>
void DomainFactory::set_initial_state(T&& state)
{
  initial_state_ = std::forward<T>(state);
}


}
