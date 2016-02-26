#include "foresight/main.h"

#include "foresight/actiontype.h"
#include "foresight/arbiter.h"
#include "foresight/domain.h"
#include "foresight/resource.h"
#include "foresight/state.h"
#include "foresight/statefactory.h"

#include <iostream>

int main() 
{
  //Program setup
  init_logger();

  //TODO: Parse command line arguments
  //TODO: Load domain
  auto domain(create_fake_domain());
  //TODO: Initialize real world
  //TODO: Create policy
  //TODO: Create arbiter
  fore::Arbiter arbiter(std::move(domain));
  //TODO: Run optimization
  arbiter.optimize();
  
  return 0;
}

void init_logger()
{
  //TODO: Logging setup?
}

fore::Domain create_fake_domain() 
{
  fore::ActionType::Map action_map;
  fore::Resource::Map resource_map;

  resource_map.emplace(1, fore::Resource(0, "Zero"));

  fore::Resource::Amount zero_amount;
  fore::Resource::Amount one_amount;
  one_amount[1] = 1;
  fore::Action::List empty_actions;
  action_map.emplace(
      10, 
      fore::ActionType(10, "Ten", 7, zero_amount, one_amount, zero_amount)
  );
  auto horizon(20);

  fore::StateFactory fact;
  auto init_state = fact.Finish();

  return fore::Domain(std::move(action_map), 
                      std::move(resource_map), 
                      horizon,
                      init_state);
}
