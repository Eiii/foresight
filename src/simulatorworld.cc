#include "foresight/simulatorworld.h"

#include "foresight/gp.h"
#include "foresight/simulator.h"
#include "foresight/nullaction.h"

#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

namespace fore { 

SimulatorWorld::SimulatorWorld(const Domain& domain) :
    domain_(domain), simulator_(domain, this), 
    current_state_(domain_.initial_state()),
    regret_(domain_), state_history() {}

void SimulatorWorld::Start() 
{
  current_state_ = domain_.initial_state();
}

void SimulatorWorld::End() 
{
  //Save the 'final' state
  state_history.push_back(current_state_);
}

bool SimulatorWorld::IsFinished() const
{
  return current_state_.time() >= domain_.horizon();
}

bool SimulatorWorld::StateIsReady(int timestep) 
{
  //Since this is fake, the next state is always ready!
  (void)timestep;
  return true;
}

State SimulatorWorld::GetState(int timestep)
{
  (void)timestep;
  assert(timestep >= current_state_.time());
  while (timestep > current_state_.time()) {
    state_history.push_back(current_state_);
    current_state_ = simulator_.AdvanceTime(current_state_);
  }
  assert(timestep == current_state_.time());
  return current_state_;
}

void SimulatorWorld::TakeAction(const Action& action)
{
  current_state_ = simulator_.BeginAction(current_state_, action);
}

std::vector<double> SimulatorWorld::FinalRegrets()
{
  std::vector<double> regrets;
  //Calculate regrets
  for (const auto& state : state_history) {
    double regret = regret_.CalculateRegret(state);
    regrets.push_back(regret);
  }
  return regrets;
}

std::vector<int> SimulatorWorld::FinalConcurrent()
{
  std::vector<int> concurrent;
  //Calculate regrets
  for (const auto& state : state_history) {
    int running = 0;
    for (const auto& action : state.running_actions()) {
      if (!is_null_action(*action)) running++;
    }
    concurrent.push_back(running);
  }
  return concurrent;
}

double SimulatorWorld::ObservationResponse(
    const State& state, 
    const Model& model, 
    Point point
) const
{
  auto gp(GP::GetGP(model, state));
  return gp->SimulatedResponse(point);

}

double SimulatorWorld::FinalRegret() 
{
  const auto& last_state(*(state_history.end()-1));
  return regret_.CalculateRegret(last_state);
}

}
