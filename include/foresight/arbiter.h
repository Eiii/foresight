#pragma once

#include "foresight/domain.h"
#include "foresight/policy.h"
#include "foresight/real.h"
#include "foresight/simulator.h"
#include "foresight/state.h"

namespace fore {

class Arbiter {
  //Constructors
  public:
    Arbiter(const Domain& domain, Policy::Ptr&& policy, 
            RealWorld::Ptr&& real_world, int start_time = 0);
    virtual ~Arbiter() = default;
    //Forbid copying
    Arbiter(const Arbiter& rhs) = delete;
    Arbiter& operator=(const Arbiter& rhs) = delete;
    //Allow moving
    Arbiter(Arbiter&& rhs) = default;
    Arbiter& operator=(Arbiter&& rhs) = default;

  //Public functions
  public:
    void Optimize();
    State CurrentState() const;

  //Private functions
  private:
    bool IsHorizonReached(const State& state) const;

  //Member variables
  private:
    const Domain& domain_;
    Policy::Ptr policy_;
    RealWorld::Ptr real_world_;
    Simulator simulator_;
    double final_regret_;
    int start_time_; //TODO: timestep type?
    std::unique_ptr<State> last_state_;
};

}
