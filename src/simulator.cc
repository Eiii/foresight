#include "foresight/simulator.h"

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
  //TODO
  (void)action;
  return state;
}

}
