#pragma once

#include "foresight/domain.h"
#include "foresight/model.h"
#include "foresight/state.h"
#include "foresight/types.h"

namespace fore {

class GP {
  //Constructors
  private:
    //Only allow construction through factory method
    GP(const Model& model, const State& state);
  public:
    virtual ~GP() = default;
  public:
    //Forbid copying
    GP(const GP& rhs) = delete;
    GP& operator=(const GP& rhs) = delete;
    //Allow moving
    GP(GP&& rhs) = default;
    GP& operator=(GP&& rhs) = default;

  //Class methods
  public:
    static GP GetGP(const Model& model, const State& state);

  //Public methods
  public:
    Point CalculateBestPoint() const;
    double CalculateMean(Point p) const;
    double SimulatedResponse(Point p) const;
};

}
