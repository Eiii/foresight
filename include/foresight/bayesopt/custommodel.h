#pragma once

#include "foresight/model.h"

#include "bayesopt.hpp"

namespace fore {

class CustomModel : public bayesopt::DiscreteModel {
  //Type aliases
  public:
    using Function = double (*) (const vectord& point);

  //Constructors
  public:
    CustomModel(const vecOfvec& valid_set, bopt_params&& params,
                Function fn, double epsilon);
    virtual ~CustomModel();
    //Forbid copying
    CustomModel(const CustomModel& rhs) = delete;
    CustomModel& operator=(const CustomModel& rhs) = delete;
    //Allow moving
    CustomModel(CustomModel&& rhs) = default;
    CustomModel& operator=(CustomModel&& rhs) = default;

  //Base functions
  public:
    virtual double evaluateSample(const vectord& Xi) override;
    virtual bool checkReachability(const vectord& query) override;

  //Static functions
  public:
    static bopt_params DefaultParams(int seed);
    static vecOfvec DefaultValidSet();
    static void DeleteParams(bopt_params* params);

  //Backing functions
  public:
    static Function GetFunction(Model::Type type);
    static double CosineFn(const vectord& Xi);

  //Getters
  public:
    const Function& function() { return function_; }
    double epsilon() { return epsilon_; }

  private:
    bopt_params params_;
    Function function_;
    double epsilon_;
};

}
