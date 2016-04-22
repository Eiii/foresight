#include "foresight/regret.h"

#include "foresight/bayesopt/custommodel.h"
#include "foresight/gp.h"

#include <cassert>
#include <limits>

namespace fore {

Regret::Regret(const Domain& domain) :
    domain_(domain),
    actual_min_(std::numeric_limits<double>::quiet_NaN()) 
{
  CalculateMinimum();
}

double Regret::CalculateRegret(const State& state)
{
  double best_mean(std::numeric_limits<double>::quiet_NaN());
  double best_real;

  for (const auto& key : domain_.models()) {
    const auto& model(key.second);
    auto fn(CustomModel::GetFunction(model.type()));
    auto gp(GP::GetGP(model, state));
    for (const auto& point : CustomModel::DefaultValidSet()) {
      //TODO: This conversion shouldn't be here-- valid set should be points
      double mean = gp->CalculateMean(vec_to_point(point));
      if (std::isnan(best_mean) || mean < best_mean) {
        best_mean = mean;
        best_real = fn(point);
      }
    }
  }
  return best_real - actual_min_;
}

void Regret::CalculateMinimum()
{
  double min = std::numeric_limits<double>::quiet_NaN();
  for (const auto& key : domain_.models()) {
    const auto& model(key.second);
    auto fn(CustomModel::GetFunction(model.type()));
    for (const auto& point : CustomModel::DefaultValidSet()) {
      double val = fn(point);
      if (std::isnan(min) || val < min) min = val;
    }
  }
  assert(!std::isnan(min));
  actual_min_ = min;
}

}
