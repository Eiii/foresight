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
#include "foresight/policies/uniform.h"
#include "foresight/simulatorworld.h"

#include <iostream>
#include <fstream>

using std::move;
using std::make_unique;
using std::vector;

int main() 
{
  int num_runs = 1;

  //Program setup
  init_logger();

  vector<vector<double>> all_regrets;
  for (int i = 0; i < num_runs; i++) {
    std::cout << "Starting run #" << i << "..." << std::endl;
    auto domain(create_fake_domain(1337+i));
    /*
    auto exp(make_unique<fore::RandomPolicy>(domain));
    auto res(make_unique<fore::RandomPolicy>(domain));
    auto policy(make_unique<fore::PairPolicy>(
          domain, move(exp), move(res))
    );
    */
    auto policy(make_unique<fore::UniformPolicy>(domain, 100));
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
  auto horizon(72);
  fore::StateFactory state_fact;
  state_fact.SetResourceAmount(1, 200);
  auto init_state(state_fact.Finish());

  fore::DomainFactory domain_fact(horizon, init_state);

  fore::ExperimentActionTypeFactory exp_act_fact(100, "Slow", 12, 1000);
  exp_act_fact.SetResourceRequirement(1, 5);
  domain_fact.AddActionType(exp_act_fact.Finish());

  exp_act_fact.Reset(101, "Medium", 8, 1000);
  exp_act_fact.SetResourceRequirement(1, 10);
  domain_fact.AddActionType(exp_act_fact.Finish());

  exp_act_fact.Reset(102, "Fast", 2, 1000);
  exp_act_fact.SetResourceRequirement(1, 20);
  domain_fact.AddActionType(exp_act_fact.Finish());

  fore::Model cosine(1000, fore::Model::Type::COSINE, seed++);

  domain_fact.AddResource(1, "Budget");
  domain_fact.AddModel(move(cosine));
  domain_fact.set_has_null_action(true);

  return domain_fact.FinishAndReset();
}
