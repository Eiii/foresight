#pragma once

#include "foresight/model.h"
#include "foresight/state.h"
#include "foresight/types.h"
#include <memory>

namespace fore {

class RealWorld {
  //Type aliases
  public:
    using Ptr = std::unique_ptr<RealWorld>;

  //Constructors
  public:
    RealWorld() = default;
    virtual ~RealWorld() = default;
    RealWorld(const RealWorld&) = delete;
    RealWorld& operator=(const RealWorld&) = delete;
    RealWorld(RealWorld&&) = default;
    RealWorld& operator=(RealWorld&&) = default;

  //Interface
  public:
    virtual void Start() = 0;
    virtual void End() = 0;
    virtual bool IsFinished() const = 0;
    virtual bool StateIsReady(int timestep) = 0;
    virtual State GetState(int timestep) = 0;
    virtual void TakeAction(const Action& action) = 0;
    virtual double ObservationResponse(
        const State& state, const Model& model, Point point
    ) const = 0;
    virtual double FinalRegret() = 0;
};

};
