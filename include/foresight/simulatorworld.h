#pragma once

#include "foresight/real.h"
#include "foresight/simulator.h"

namespace fore {

class SimulatorWorld : public RealWorld {
  //Constructors
  public:
    SimulatorWorld(const Domain& domain);
    virtual ~SimulatorWorld() = default;
    SimulatorWorld(const SimulatorWorld&) = delete;
    SimulatorWorld& operator=(const SimulatorWorld&) = delete;
    SimulatorWorld(SimulatorWorld&&) = default;
    SimulatorWorld& operator=(SimulatorWorld&&) = default;

  //Interface functions
  public:
    virtual void Start() override;
    virtual void End() override;
    virtual bool IsFinished() override;
    virtual bool StateIsReady(int timestep) override;
    virtual State GetState(int timestep) override;
    virtual void TakeAction(const Action& action) override;

  //Private member variables
  private:
    const Domain& domain_;
    Simulator simulator_;
    State current_state;
};

}

