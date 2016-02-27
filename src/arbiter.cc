#include "foresight/arbiter.h"

#include <iostream>

using std::move;
using std::cout;
using std::endl;

namespace fore {

Arbiter::Arbiter(Domain&& domain) :
    domain_(move(domain)), simulator_(domain_) {}

void Arbiter::Optimize() const 
{
  cout << "Starting optimization..." << endl;
  cout << domain_.Info() << endl;
  auto state(domain_.initial_state());
  cout << state.Info() << endl;

  while (!IsHorizonReached(state)) {
    state = simulator_.AdvanceTime(state);
    cout << state.Info() << endl;
  }
  cout << "Finished!" << endl;
}

bool Arbiter::IsHorizonReached(const State& state) const
{
  return state.time() >= domain_.horizon();
}

}
