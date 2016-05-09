#include "foresight/simulatorworld.h"
#include "foresight/simulator.h"

#include <cassert>
#include <iostream>

using std::cout;
using std::endl;

namespace fore { 

SimulatorWorld::SimulatorWorld(const Domain& domain) :
    domain_(domain), simulator_(domain), 
    current_state(domain_.initial_state()),
    regret_(domain_), state_history() {}

void SimulatorWorld::Start() 
{
  //TODO: Blank
}

void SimulatorWorld::End() 
{
  //Save the 'final' state
  state_history.push_back(current_state);
}

bool SimulatorWorld::IsFinished() 
{
  return current_state.time() >= domain_.horizon();
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
  assert(timestep >= current_state.time());
  while (timestep > current_state.time()) {
    state_history.push_back(current_state);
    current_state = simulator_.AdvanceTime(current_state);
  }
  assert(timestep == current_state.time());
  return current_state;
}

void SimulatorWorld::TakeAction(const Action& action)
{
  current_state = simulator_.BeginAction(current_state, action);
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

}
