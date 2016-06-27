#include "foresight/policies/smartuniform.h"
#include "foresight/policies/uniform.h"
#include "foresight/nullaction.h"
#include "foresight/arbiter.h"
#include "foresight/fakeworld.h"
#include "foresight/gp.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

namespace fore {

SmartUniformPolicy::SmartUniformPolicy(
    const Domain& domain, ActionType::Id id1, ActionType::Id id2
) :
    Policy(domain),
    policy1_(new UniformPolicy(domain_, id1)),
    policy2_(new UniformPolicy(domain_, id2)),
    switched_(false),
    last_time_tested_(-6)
{ }

SmartUniformPolicy::SmartUniformPolicy(const SmartUniformPolicy& rhs) :
    Policy(rhs),
    policy1_(rhs.policy1_->Clone()),
    policy2_(rhs.policy2_->Clone()),
    switched_(rhs.switched_),
    last_time_tested_(rhs.last_time_tested_) {}

SmartUniformPolicy& SmartUniformPolicy::operator=
  (
    const SmartUniformPolicy& rhs
  )
{
  SmartUniformPolicy p(rhs);
  std::swap(*this, p);
  return *this;
}

Action::Ptr SmartUniformPolicy::SelectAction(const State& state)
{
  cout << "SELECTING..." << endl;
  //If we haven't switched yet, see if we should switch now
  if (!switched_ && state.time() > last_time_tested_+5) {
    //Run simulations of policies using our current understanding
    //of the problem as the 'real world'
    double p1_improve(SimulatePolicy(policy1_, state, 0));
    double p2_improve(SimulatePolicy(policy2_, state, 1));
    
    //Switch to the better policy
    if (p2_improve > p1_improve) switched_ = true;
    last_time_tested_ = state.time();
  }
  
  
  if (!switched_) {
    return policy1_->SelectAction(state);
  } else {
    return policy2_->SelectAction(state);
  }
}

double SmartUniformPolicy::SimulatePolicy(
    Policy::Ptr& policy, const State& state, int seed
) const
{
  constexpr int samples = 10;
  cout << "STARTING SIMULATION @ " << state.time() << endl;
  double avg_regret(0);
  for (int i = 0; i < samples; i++) {
    int temp_seed = seed + i * 10 + state.time() * 10000;
    auto fake_world(std::make_unique<FakeWorld>(domain_, state, temp_seed));
    Arbiter arbiter(domain_, policy->Clone(), 
                    std::move(fake_world), state.time());
    arbiter.Optimize();
    auto last_state(arbiter.CurrentState());
    avg_regret += Improvement(state, last_state);
  }
  avg_regret /= (double)samples;
  cout << "FINISHED SIMULATION: " << avg_regret << endl;
  return avg_regret;
}

double SmartUniformPolicy::Improvement(const State& first, 
                                       const State& second) const
{
  double first_best(std::numeric_limits<double>::quiet_NaN());
  double second_best(std::numeric_limits<double>::quiet_NaN());
  for (const auto& key : domain_.models()) {
    const auto& model(key.second);
    auto first_gp(GP::GetGP(model, first)); //TODO: First can be precalc'd
    for (const auto& point : CustomModel::DefaultValidSet()) {
      double val(first_gp->CalculateMean(vec_to_point(point)));
      if (std::isnan(first_best) || val > first_best) first_best = val;
    }
    auto second_gp(GP::GetGP(model, second));
    for (const auto& point : CustomModel::DefaultValidSet()) {
      double val(second_gp->CalculateMean(vec_to_point(point)));
      if (std::isnan(second_best) || val > second_best) second_best = val;
    }
  }

  double improvement(second_best-first_best);
  return std::max(improvement, 0.0);
}

Policy::Ptr SmartUniformPolicy::Clone() const
{
  return std::make_unique<SmartUniformPolicy>(*this);
}

}
