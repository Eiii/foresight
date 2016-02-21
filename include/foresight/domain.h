#pragma once

namespace fore {

class Domain {
  public:
    //Constructors
    Domain() = default;
    virtual ~Domain() = default;
    //Forbid copying
    Domain(const Domain& other) = delete;
    Domain& operator=(const Domain& other) = delete;
    //Allow moving
    Domain(Domain&& rhs) = default;
    Domain& operator=(Domain& rhs) = default;
};

}
