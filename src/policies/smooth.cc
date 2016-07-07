#include "foresight/policies/smooth.h"

#include <cmath>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

namespace fore {

SmoothPolicy::SmoothPolicy(
    const Domain& domain, ActionType::Id id
) :
    UniformPolicy(domain, id)
{
  actions_per_step_ = CalcActionsPerStep(domain_);
}

Policy::Ptr SmoothPolicy::Clone() const
{
  return std::make_unique<SmoothPolicy>(*this);
}

vector<int> SmoothPolicy::CalcActionsPerStep(const Domain& domain) const
{
  auto horizon(domain.horizon());
  const auto& action(domain_.action_type(action_id_));
  auto duration(action.duration().mean());
  auto width(horizon/duration);
  auto initial_amt(domain.initial_state().resources());

  auto aps(vector<int>(horizon+1, 0));
  for (int t = 0; t < horizon; t++) aps[t] = 1;

  auto req(action.requires());
  auto leftover_res(initial_amt-req*width);
  auto remaining_exp(leftover_res/req);
  auto height(static_cast<int>(remaining_exp*2.0/width));
  auto slope(static_cast<double>(height)/static_cast<double>(width));

  cout << remaining_exp << " / " << width << " / " << height;
  cout << " / " << slope << endl;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < duration; j++) {
      auto t = i*duration+j;
      aps[t] += height-static_cast<int>(std::ceil(slope*i));
    }
  }
  return aps;
}

}
