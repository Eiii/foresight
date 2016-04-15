#include "foresight/policies/random.h"

#include <cassert>

namespace fore {

RandomPolicy::RandomPolicy(const Domain& domain) :
    Policy(domain) {}

Action::Ptr RandomPolicy::SelectAction(const State& state)
{
  auto legal_actions(simulator_.LegalActions(state));
  assert(legal_actions.size() > 0);
  return legal_actions[0]->Clone();
}

}
