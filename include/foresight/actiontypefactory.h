#pragma once

#include "foresight/actiontype.h"

namespace fore {

class ActionTypeFactory {
  //Constructors
  public:
    ActionTypeFactory(int id, std::string name, Duration duration);
    virtual ~ActionTypeFactory() = default;
    ActionTypeFactory(const ActionTypeFactory& rhs) = default;
    ActionTypeFactory& operator=(const ActionTypeFactory& rhs) = default;
    ActionTypeFactory(ActionTypeFactory&& rhs) = default;
    ActionTypeFactory& operator=(ActionTypeFactory&& rhs) = default;

  //Public functions
  public:
    virtual ActionType::Ptr Finish() const;
    void Reset(ActionType::Id id, std::string name, Duration duration);
    void SetResourceRequirement(Resource::Id id, int amount);
    void SetResourceProduction(Resource::Id id, int amount);
    void SetResourceUpkeep(Resource::Id id, int amount);

  //Setters
  public:
    void set_id(ActionType::Id id) { id_ = id; }
    void set_cancelable(bool cancelable) { cancelable_ = cancelable; }
    template<typename T>
    void set_name(T&& name);
    template<typename T>
    void set_duration(T&& duration);
    template<typename T>
    void set_requires(T&& requires);
    template<typename T>
    void set_produces(T&& produces);
    template<typename T>
    void set_upkeep(T&& upkeep);

  //Member variables
  private:
    ActionType::Id id_;
    std::string name_;
    Duration duration_;
    bool cancelable_;
    Resource::Amount requires_;
    Resource::Amount produces_;
    Resource::Amount upkeep_;
};

//Template implementations
template<typename T>
void ActionTypeFactory::set_name(T&& name)
{
  name_ = std::forward<T>(name);
}

template<typename T>
void ActionTypeFactory::set_duration(T&& duration)
{
  duration_ = std::forward<T>(duration);
}

template<typename T>
void ActionTypeFactory::set_requires(T&& requires)
{
  requires_ = std::forward<T>(requires);
}

template<typename T>
void ActionTypeFactory::set_produces(T&& produces)
{
  produces_ = std::forward<T>(produces);
}

template<typename T>
void ActionTypeFactory::set_upkeep(T&& upkeep)
{
  upkeep_ = std::forward<T>(upkeep);
}
}
