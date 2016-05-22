#include "foresight/policy.h"
#include "foresight/nullaction.h"

#include <cassert>

namespace fore {

Policy::Policy(const Domain& domain) :
    domain_(domain), simulator_(domain_) { };

std::unique_ptr<Action> Policy::FindAction(const State& state, ACTIONID id)
{
  auto legal_actions(simulator_.LegalActions(state));
  for (auto& action_ptr : legal_actions) {
    if (action_ptr->type_id() == id) {
      return std::move(action_ptr);
    }
  }
  assert(false);
  return std::move(legal_actions[0]);
}

std::unique_ptr<Action> Policy::FindNullAction(const State& state)
{
  auto legal_actions(simulator_.LegalActions(state));
  for (auto& action_ptr : legal_actions) {
    if (is_null_action(*action_ptr)) {
      return std::move(action_ptr);
    }
  }
  assert(false);
  return std::move(legal_actions[0]);
}

}
