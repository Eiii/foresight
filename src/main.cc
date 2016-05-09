#include "foresight/main.h"

#include "foresight/actiontypefactory.h"
#include "foresight/arbiter.h"
#include "foresight/domainfactory.h"
#include "foresight/experimentactiontypefactory.h"
#include "foresight/resource.h"
#include "foresight/statefactory.h"
#include "foresight/policies/human.h"
#include "foresight/policies/random.h"
#include "foresight/policies/pair.h"
#include "foresight/simulatorworld.h"

#include <iostream>
#include <fstream>

using std::move;
using std::make_unique;
using std::vector;

int main() 
{
  int num_runs = 25;

  //Program setup
  init_logger();

  vector<vector<double>> all_regrets;
  for (int i = 0; i < num_runs; i++) {
    std::cout << "Starting run #" << i << "..." << std::endl;
    auto domain(create_fake_domain(1337+i));
    auto exp(make_unique<fore::RandomPolicy>(domain));
    auto res(make_unique<fore::RandomPolicy>(domain));
    auto policy(make_unique<fore::PairPolicy>(
          domain, move(exp), move(res))
    );
    fore::RealWorld::Ptr real(new fore::SimulatorWorld(domain));
    fore::SimulatorWorld& sim_world(
        static_cast<fore::SimulatorWorld&>(*real)
    );
    fore::Arbiter arbiter(domain, move(policy), move(real));
    arbiter.Optimize();
    auto regret_list(sim_world.FinalRegrets());
    all_regrets.push_back(regret_list);
    std::cout << "Done!" << std::endl;
  }

  //Calculate average regret at each timestep
  std::ofstream output("regrets.csv");
  for (const auto& regrets : all_regrets) {
    for (unsigned int i = 0; i < regrets.size(); i++) {
      output << regrets[i];
      if (i != regrets.size()-1) output << ", ";
    }
    output << std::endl;
  }

  return 0;
}

void init_logger()
{
  //TODO: Logging setup?
}

fore::Domain create_fake_domain(int seed) 
{
  auto horizon(90);
  fore::StateFactory state_fact;
  state_fact.SetResourceAmount(1, 2);
  state_fact.SetResourceAmount(2, 5);
  state_fact.SetResourceAmount(10, 1);
  state_fact.SetResourceAmount(11, 1);
  state_fact.SetResourceAmount(12, 1);
  auto init_state(state_fact.Finish());

  fore::DomainFactory domain_fact(horizon, init_state);
  fore::ActionTypeFactory action_fact(100, "Produce A", 5);
  action_fact.SetResourceRequirement(1, 1);
  action_fact.SetResourceProduction(1, 1);
  action_fact.SetResourceProduction(10, 3);
  domain_fact.AddActionType(action_fact.Finish());

  action_fact.Reset(101, "Produce B", 5);
  action_fact.SetResourceRequirement(1, 1);
  action_fact.SetResourceProduction(1, 1);
  action_fact.SetResourceProduction(11, 3);
  domain_fact.AddActionType(action_fact.Finish());

  action_fact.Reset(102, "Produce C", 5);
  action_fact.SetResourceRequirement(1, 1);
  action_fact.SetResourceProduction(1, 1);
  action_fact.SetResourceProduction(12, 3);
  domain_fact.AddActionType(action_fact.Finish());

  fore::ExperimentActionTypeFactory exp_act_fact(110, "Experiment A", 5, 1000);
  exp_act_fact.SetResourceRequirement(10, 1);
  exp_act_fact.SetResourceRequirement(2, 1);
  exp_act_fact.SetResourceProduction(2, 1);
  domain_fact.AddActionType(exp_act_fact.Finish());

  exp_act_fact.Reset(111, "Experiment B", 5, 1001);
  exp_act_fact.SetResourceRequirement(11, 1);
  exp_act_fact.SetResourceRequirement(2, 1);
  exp_act_fact.SetResourceProduction(2, 1);
  domain_fact.AddActionType(exp_act_fact.Finish());

  exp_act_fact.Reset(112, "Experiment C", 5, 1002);
  exp_act_fact.SetResourceRequirement(12, 1);
  exp_act_fact.SetResourceRequirement(2, 1);
  exp_act_fact.SetResourceProduction(2, 1);
  domain_fact.AddActionType(exp_act_fact.Finish());

  fore::Model m1(1000, fore::Model::Type::ROSENBROCK, seed++);
  fore::Model m2(1001, fore::Model::Type::RASTRIGIN, seed++);
  fore::Model cosine(1002, fore::Model::Type::COSINE, seed++);

  domain_fact.AddResource(1, "Resource Lab");
  domain_fact.AddResource(2, "Experiment Lab");
  domain_fact.AddResource(10, "Resource A");
  domain_fact.AddResource(11, "Resource B");
  domain_fact.AddResource(12, "Resource C");
  domain_fact.AddModel(move(m1));
  domain_fact.AddModel(move(m2));
  domain_fact.AddModel(move(cosine));

  return domain_fact.FinishAndReset();
}
