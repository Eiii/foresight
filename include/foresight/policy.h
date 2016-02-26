#pragma once

#include "foresight/domain.h"

#include <memory>

namespace fore {

class Policy {
  public:
    Policy(const Domain& domain);
    virtual ~Policy() = default;
    Policy(const Policy& rhs) = default;
    Policy& operator=(const Policy& rhs) = default;
    Policy(Policy&& rhs) = default;
    Policy& operator=(Policy&& rhs) = default;

    //TODO: Fill signature
    virtual std::unique_ptr<Action> SelectAction(const State& state) = 0;

  private:
    const Domain& domain_;
};

}
