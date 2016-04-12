#include "foresight/policies/human.h"

#include <cassert>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

namespace fore {

HumanPolicy::HumanPolicy(const Domain& domain) :
    SimulatorPolicy(domain) {}

Action::Ptr HumanPolicy::SelectAction(const State& state)
{
  auto legal_actions(simulator_.LegalActions(state));
  assert(legal_actions.size() > 0);
  int idx_id(0);
  cout << "Legal actions: " << endl;
  for (const auto& action_ptr : legal_actions) {
    cout << "\t" << ++idx_id << ": "; 
    cout << action_ptr->Info(domain()) << endl;
  }
  //Get key from user
  int choice;
  cin >> choice;

  return std::move(legal_actions[choice-1]);
}

}
