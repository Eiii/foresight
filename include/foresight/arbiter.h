#pragma once

#include "foresight/domain.h"

namespace fore {

class Arbiter {
  public:
    //Constructors
    Arbiter(Domain&& domain);
    virtual ~Arbiter() = default;
    //Forbid copying
    Arbiter(const Arbiter& rhs) = delete;
    Arbiter& operator=(const Arbiter& rhs) = delete;
    //Allow moving
    Arbiter(Arbiter&& rhs) = default;
    Arbiter& operator=(Arbiter&& rhs) = default;

  private:
    Domain _domain;
};

}
