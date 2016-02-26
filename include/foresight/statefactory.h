#pragma once

#include "foresight/state.h"

namespace fore {

class StateFactory {
  //Constructors
  public:
    StateFactory();
    StateFactory(const State& state);
    StateFactory(int timestep);
    virtual ~StateFactory() = default;
    StateFactory(const StateFactory& rhs) = default;
    StateFactory& operator=(const StateFactory& rhs) = default;
    StateFactory(StateFactory&& rhs) = default;
    StateFactory& operator=(StateFactory&& rhs) = default;

  //Public functions
  public:
    State Finish() const;
    void Reset();
    void Copy(const State& state);
    void SetResourceAmount(Resource::Id id, int amount);
    template<typename... Args>
    void AddRunningAction(Args&&... args);

  //Setters
  public:
    void set_timestep(int time) { timestep_ = time; }
    template <typename T> 
    void set_resources(T&& resources);
    template <typename T>
    void set_running_actions(T&& running_actions);
  
  //Member variables:
  private:
    int timestep_;
    Resource::Amount resources_;
    Action::List running_actions_;
};

template<typename... Args>
void StateFactory::AddRunningAction(Args&&... args)
{
  running_actions_.emplace_back(std::forward<Args>(args)...);
}

template <typename T> 
void StateFactory::set_resources(T&& resources)
{
  resources_ = std::forward<T>(resources);
}

template <typename T>
void StateFactory::set_running_actions(T&& running_actions) 
{
  running_actions_ = std::forward<T>(running_actions);
}


}
