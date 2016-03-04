#pragma once

#include "foresight/domain.h"

#include <memory>

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

  //Protected getters
  protected:
    const auto& domain() const { return domain_; }

  //Private member variables
  private:
    const Domain& domain_;
};

}
