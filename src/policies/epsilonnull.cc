#include "foresight/policies/epsilonnull.h"

#include <cassert>

#include "foresight/nullaction.h"

namespace fore {

EpsilonNullPolicy::EpsilonNullPolicy(
    const Domain& domain, double epsilon, int seed
) :
    Policy(domain), random_(seed), epsilon_(epsilon) {}

Action::Ptr EpsilonNullPolicy::SelectAction(const State& state)
{
  assert(domain_.has_null_action());
  RandomReal rand(random_, UniformRealDist(0, 1));

  auto legal_actions(simulator_.LegalActions(state));
  if (rand() < epsilon_) {
    for (auto& action : legal_actions) {
      if (is_null_action(*action)) {
        return std::move(action);        
      }
    }
    assert(false); //ERROR-- we should ALWAYS find the null action!
    return std::move(legal_actions[0]);
  } else {
    assert(legal_actions.size() > 0);
    RandomInt rand(random_, UniformIntDist(0, legal_actions.size()-1));
    return legal_actions[rand()]->Clone();
  }
}

Policy::Ptr EpsilonNullPolicy::Clone() const
{
  return std::make_unique<EpsilonNullPolicy>(*this);
}

}
