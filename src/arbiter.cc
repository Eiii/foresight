#include "foresight/arbiter.h"

#include <iostream>

using std::move;
using std::cout;
using std::endl;

namespace fore {

Arbiter::Arbiter(Domain&& domain) :
    domain_(move(domain)) {}

void Arbiter::optimize() const 
{
  cout << "Starting optimization..." << endl;
  cout << domain_.info() << endl;
  auto state(domain_.initial_state());
  cout << state.info() << endl;
  cout << "Finished!" << endl;
}

}
