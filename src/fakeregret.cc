#include "foresight/fakeregret.h"

#include "foresight/bayesopt/custommodel.h"
#include "foresight/gp.h"

namespace fore {

FakeRegret::FakeRegret(const Domain& domain, const State& state) :
    Regret(domain)
{
  CalculateMinimumWithState(state);
}

void FakeRegret::CalculateMinimumWithState(const State& state)
{
  double min = std::numeric_limits<double>::quiet_NaN();
  for (const auto& key : domain_.models()) {
    const auto& model(key.second);
    auto gp(GP::GetGP(model, state));
    for (const auto& point : CustomModel::DefaultValidSet()) {
      double val(gp->CalculateMean(vec_to_point(point)));
      if (std::isnan(min) || val < min) min = val;
    }
  }
  assert(!std::isnan(min));
  actual_min_ = min;
}

}
