#include "foresight/simulator.h"

#include <cassert>

namespace fore {

Simulator::Simulator(const Domain& domain) :
    domain_(domain) {}

State Simulator::AdvanceTime(const State& state)
{
  //TODO
  return state;
}

State Simulator::BeginAction(const State& state, const Action& action)
{
  assert(action.time_started() == state.timestep());
  (void)action;
  return state;
}

}
