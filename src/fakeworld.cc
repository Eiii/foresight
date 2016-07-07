#include "foresight/fakeworld.h"

#include "foresight/gp.h"
#include "foresight/simulator.h"

//From bayesopt-- kind of a hack
#include "gauss_distribution.hpp"

#include <iostream>
using std::cout;
using std::endl;

namespace fore { 

FakeWorld::FakeWorld(const Domain& domain, const State& state, int seed) :
    domain_(domain), simulator_(domain, this), 
    current_state_(state), starting_state_(state), control_state_(state),
    regret_(domain_, state), random_(seed) {}

void FakeWorld::Start() 
{
  current_state_ = starting_state_;
}

void FakeWorld::End() 
{
  //BLANK
}

bool FakeWorld::IsFinished() const
{
  return current_state_.time() >= domain_.horizon();
}

bool FakeWorld::StateIsReady(int timestep) 
{
  //Since this is fake, the next state is always ready!
  (void)timestep;
  return true;
}

State FakeWorld::GetState(int timestep)
{
  (void)timestep;
  assert(timestep >= current_state_.time());
  while (timestep > current_state_.time()) {
    current_state_ = simulator_.AdvanceTime(current_state_);
  }
  assert(timestep == current_state_.time());
  return current_state_;
}

void FakeWorld::TakeAction(const Action& action)
{
  current_state_ = simulator_.BeginAction(current_state_, action);
}

double FakeWorld::ObservationResponse(
    const State& state, 
    const Model& model, 
    Point point
) const
{
  auto gp(GP::GetGP(model, state));
  //Calculate mean&std at point based on control state
  auto mean_std(gp->CalculateMeanAndStd(point));
  bayesopt::GaussianDistribution dist(random_);
  dist.setMeanAndStd(mean_std.first, mean_std.second);
  double result(dist.sample_query());
  cout << point << ", " << mean_std.first << " / " << mean_std.second;
  cout << " = " << result << endl;
  return result;
}

double FakeWorld::FinalRegret() 
{
  return regret_.CalculateRegret(current_state_);
}

}
