#pragma once

#include "foresight/domain.h"
#include "foresight/simulator.h"

#include <memory>

#define ACTIONID int

namespace fore {

class Policy {
  //Public typedefs
  public:
    using Ptr = std::unique_ptr<Policy>;

  //Constructors
  public:
    Policy(const Domain& domain);
    virtual ~Policy() = default;
    Policy(const Policy& rhs) = default;
    Policy& operator=(const Policy& rhs) = default;
    Policy(Policy&& rhs) = default;
    Policy& operator=(Policy&& rhs) = default;

  //Public functions
  public:
    virtual std::unique_ptr<Action> SelectAction(const State& state) = 0;
    virtual Ptr Clone() const = 0;

  //Protected functions
  public:
    std::unique_ptr<Action> FindAction(const State& state, ACTIONID id);
    std::unique_ptr<Action> FindNullAction(const State& state);

  //Protected member variables
  protected:
    const Domain& domain_;
    Simulator simulator_;
};

}
