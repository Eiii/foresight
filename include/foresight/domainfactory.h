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
    void AddActionType(ActionType::Ptr&& action_ptr);
    void AddModel(Model&& model);
    template<typename... Args>
    void AddResource(Args&&... args);

  //Template setters
  public:
    void set_horizon(int horizon) { horizon_ = horizon; }
    void set_has_null_action(bool has) { has_null_action_ = has; }
    template<typename T>
    void set_action_types(T&& action_types);
    template<typename T>
    void set_resources(T&& resources);
    template<typename T>
    void set_models(T&& models);
    template<typename T>
    void set_initial_state(T&& state);

  //Member variables
  private:
    ActionType::Map action_types_;
    Resource::Map resources_;
    Model::Map models_;
    int horizon_;
    bool has_null_action_;
    State initial_state_;
};

//Template implementations
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
void DomainFactory::set_models(T&& models)
{
  resources_ = std::forward<T>(models);
}

template<typename T>
void DomainFactory::set_initial_state(T&& state)
{
  initial_state_ = std::forward<T>(state);
}

}
