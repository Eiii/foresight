#pragma once

#include "foresight/real.h"
#include "foresight/regret.h"
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
  public: //TODO: const these functions!
    void Start() override;
    void End() override;
    bool IsFinished() const override;
    bool StateIsReady(int timestep) override;
    State GetState(int timestep) override;
    void TakeAction(const Action& action) override;
    double ObservationResponse(const State& state, const Model& model, 
                               Point point) const override;

  //Public functions
  public:
    std::vector<double> FinalRegrets();
    std::vector<int> FinalConcurrent();

  //Private member variables
  private:
    const Domain& domain_;
    Simulator simulator_;
    State current_state_;
    Regret regret_;
    std::vector<State> state_history;
};

}

