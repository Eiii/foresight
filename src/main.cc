#include "foresight/main.h"

#include "foresight/actiontypefactory.h"
#include "foresight/arbiter.h"
#include "foresight/domainfactory.h"
#include "foresight/resource.h"
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
  auto horizon(20);
  fore::StateFactory state_fact;
  state_fact.SetResourceAmount(10, 2);
  state_fact.AddRunningAction(7, 0);
  auto init_state(state_fact.Finish());

  fore::DomainFactory domain_fact(horizon, init_state);
  fore::ActionTypeFactory action_fact(7, "ASeven", 12);
  action_fact.SetResourceProduction(10, 1);
  domain_fact.AddActionType(action_fact.Finish());
  domain_fact.AddResource(10, "RTen");

  return domain_fact.FinishAndReset();
}
