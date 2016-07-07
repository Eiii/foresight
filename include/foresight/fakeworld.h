#pragma once

#include "foresight/real.h"
#include "foresight/fakeregret.h"
#include "foresight/simulator.h"
#include "foresight/util/random.h"

namespace fore {

class FakeWorld : public RealWorld {
  //Constructors
  public:
    FakeWorld(const Domain& domain, const State& state, int seed);
    virtual ~FakeWorld() = default;
    FakeWorld(const FakeWorld&) = delete;
    FakeWorld& operator=(const FakeWorld&) = delete;
    FakeWorld(FakeWorld&&) = default;
    FakeWorld& operator=(FakeWorld&&) = default;

  //Interface functions
  public:
    void Start() override;
    void End() override;
    bool IsFinished() const override;
    bool StateIsReady(int timestep) override;
    State GetState(int timestep) override;
    void TakeAction(const Action& action) override;
    double ObservationResponse(const State& state, const Model& model, 
                               Point point) const override;
    double FinalRegret() override;

  //Private member variables
  private:
    const Domain& domain_;
    Simulator simulator_;
    State current_state_;
    State starting_state_;
    State control_state_;
    FakeRegret regret_;
    mutable RandomEngine random_;
};

}

