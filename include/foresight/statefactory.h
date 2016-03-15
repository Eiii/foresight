#pragma once

#include "foresight/state.h"

namespace fore {

class StateFactory {
  //Constructors
  public:
    StateFactory();
    StateFactory(const State& state);
    StateFactory(int time);
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
    void AddObservation(Model::Id id, Point p, double result);
    void AddFalseObservation(Model::Id id, Point p, double result);
    void RemoveFalseObservation(Model::Id id, Point p, double result);

  //Getters
  public:
    const auto& time() const { return time_; }
    const auto& resources() const { return resources_; }
    const auto& running_actions() const { return running_actions_; }
    const auto& observations() const { return observations_; }
    const auto& fales_observations() const { return false_observations_; }

  //Setters
  public:
    void set_time(int time) { time_ = time; }
    template <typename T> 
    void set_resources(T&& resources);
    template <typename T>
    void set_running_actions(T&& running_actions);
    template <typename T>
    void set_observations(T&& observations);
    template <typename T>
    void set_false_observations(T&& false_observations);
  
  //Member variables:
  private:
    int time_;
    Resource::Amount resources_;
    Action::List running_actions_;
    Model::ObsMap observations_;
    Model::ObsMap false_observations_;
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

template <typename T>
void StateFactory::set_observations(T&& observations)
{
  observations_ = std::forward<T>(observations);
}

template <typename T>
void StateFactory::set_false_observations(T&& false_observations)
{
  false_observations_ = std::forward<T>(false_observations);
}


}
