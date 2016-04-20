#include "foresight/simulatorworld.h"
#include "foresight/simulator.h"

#include <cassert>

namespace fore { 

SimulatorWorld::SimulatorWorld(const Domain& domain) :
    domain_(domain), simulator_(domain), 
    current_state(domain_.initial_state()) {}

bool SimulatorWorld::IsFinished() 
{
  return current_state.time() >= domain_.horizon();
}

bool SimulatorWorld::StateIsReady(int timestep) 
{
  (void)timestep;
  return true;
}

State SimulatorWorld::GetState(int timestep)
{
  (void)timestep;
  assert(timestep >= current_state.time());
  while (timestep > current_state.time()) {
    current_state = simulator_.AdvanceTime(current_state);
  }
  assert(timestep == current_state.time());
  return current_state;
}

void SimulatorWorld::TakeAction(const Action& action)
{
  current_state = simulator_.BeginAction(current_state, action);
}

}
