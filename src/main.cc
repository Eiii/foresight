#include "foresight/main.h"

#include "foresight/actiontypefactory.h"
#include "foresight/arbiter.h"
#include "foresight/domainfactory.h"
#include "foresight/experimentactiontypefactory.h"
#include "foresight/resource.h"
#include "foresight/statefactory.h"
#include "foresight/policies/human.h"

#include <iostream>

int main() 
{
  //Program setup
  init_logger();

  //TODO: Parse command line arguments
  //TODO: Load domain
  auto domain(create_fake_domain());
  //TODO: Initialize real world
  auto policy(std::make_unique<fore::HumanPolicy>(domain));
  //TODO: Create arbiter
  fore::Arbiter arbiter(domain, std::move(policy));
  //TODO: Run optimization
  arbiter.Optimize();
  
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
  state_fact.SetResourceAmount(11, 1);
  auto init_state(state_fact.Finish());

  fore::DomainFactory domain_fact(horizon, init_state);
  fore::ActionTypeFactory action_fact(7, "Produce A", 4);
  action_fact.SetResourceRequirement(11, 1);
  action_fact.SetResourceProduction(10, 1);
  action_fact.SetResourceProduction(11, 1);

  fore::ExperimentActionTypeFactory exp_act_fact(8, "Experiment A", 4, 0);
  exp_act_fact.set_cancelable(true);
  exp_act_fact.SetResourceRequirement(10, 1);

  domain_fact.AddActionType(exp_act_fact.Finish());
  domain_fact.AddActionType(action_fact.Finish());
  domain_fact.AddResource(10, "Resource A");
  domain_fact.AddResource(11, "Labs");

  return domain_fact.FinishAndReset();
}
