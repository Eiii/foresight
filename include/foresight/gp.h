#pragma once

#include "foresight/domain.h"
#include "foresight/model.h"
#include "foresight/state.h"
#include "foresight/types.h"

#include "foresight/bayesopt/custommodel.h"

namespace fore {

class GP {
  //Constructors
  public: //TODO: Why can't this be private?
    //Ideally only allow construction through factory method
    GP(CustomModel::Function fn, const Model& model, const State& state);
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
    static std::shared_ptr<GP> GetGP(const Model& model, const State& state);

  //Public methods
  public:
    Point CalculateBestPoint() const;
    std::pair<double, double> CalculateMeanAndStd(Point p) const;
    double CalculateMean(Point p) const;
    double CalculateStd(Point p) const;
    double SimulatedResponse(Point p) const; //TODO: This should really be renamed

  //Private methods
  private:
    void InitializeModel(const Model& model, const State& state);

  //Member functions
  private:
    mutable CustomModel model_; //TODO: I wish this wasn't necessary
};

vectord point_to_vec(const fore::Point& p);
fore::Point vec_to_point(const vectord& v);

}
