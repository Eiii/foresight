#include "foresight/policies/random.h"

#include <cassert>

namespace fore {

RandomPolicy::RandomPolicy(const Domain& domain, int seed) :
    Policy(domain), random_(seed) {}

Action::Ptr RandomPolicy::SelectAction(const State& state)
{
  auto legal_actions(simulator_.LegalActions(state));
  assert(legal_actions.size() > 0);
  RandomInt rand(random_, UniformIntDist(0, legal_actions.size()-1));
  return legal_actions[rand()]->Clone();
}

Policy::Ptr RandomPolicy::Clone() const {
  return std::make_unique<RandomPolicy>(*this);
}

}
