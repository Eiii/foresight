#pragma once

#include "foresight/domain.h"
#include "foresight/state.h"

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

    void optimize() const;

  private:
    Domain domain_;
};

}
