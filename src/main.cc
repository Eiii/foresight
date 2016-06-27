#include "foresight/main.h"

#include "foresight/actiontypefactory.h"
#include "foresight/arbiter.h"
#include "foresight/domainfactory.h"
#include "foresight/experimentactiontypefactory.h"
#include "foresight/resource.h"
#include "foresight/statefactory.h"
#include "foresight/simulatorworld.h"
#include "foresight/policies/uniform.h"
#include "foresight/policies/upfront.h"

#include <iostream>
#include <fstream>
#include <string>

using std::move;
using std::make_unique;
using std::vector;
using std::string;
using std::function;

constexpr int num_runs = 20;

template<typename T>
void evaluate_uniform(function<fore::Domain (int)> fn, string ofname, int id1);

int main(int argc, char *argv[]) 
{
  assert(argc == 3); (void)argc;
  std::string arg(argv[1]), domain(argv[2]);
  function<fore::Domain (int)> fn;
  std::string name(arg);
  if (domain == "big") {
    name = "b_"+name;
    fn = test_domain_large; 
  } else {
    fn = test_domain;
  }
  if (arg == "uniform") {
    evaluate_uniform<fore::UniformPolicy>(fn, name, 100);
  } else if (arg == "upfront") {
    evaluate_uniform<fore::UpfrontPolicy>(fn, name, 100);
  }
  return 0;
}

template<typename T>
void evaluate_uniform(function<fore::Domain (int)> fn, string ofname, int id1)
{
  vector<vector<double>> all_regrets;
  vector<vector<int>> all_concur;
  for (int i = 0; i < num_runs; i++) {
    std::cout << "Starting run #" << i << "..." << std::endl;
    auto domain(fn(1337+i));
    auto policy(make_unique<T>(domain, id1));
    fore::RealWorld::Ptr real(new fore::SimulatorWorld(domain));
    fore::SimulatorWorld& sim_world(
        static_cast<fore::SimulatorWorld&>(*real)
    );
    fore::Arbiter arbiter(domain, move(policy), move(real));
    arbiter.Optimize();
    all_regrets.push_back(sim_world.FinalRegrets());
    all_concur.push_back(sim_world.FinalConcurrent());
  }

  //Calculate average regret at each timestep
  string regret_name = ofname + "_regret.csv";
  std::ofstream output(regret_name.c_str());
  for (const auto& regrets : all_regrets) {
    for (unsigned int i = 0; i < regrets.size(); i++) {
      output << regrets[i];
      if (i != regrets.size()-1) output << ", ";
    }
    output << std::endl;
  }
  output.close();

  //Calculate average running actions at each timestep
  string running_name = ofname + "_running.csv";
  output.open(running_name.c_str());
  for (const auto& regrets : all_concur) {
    for (unsigned int i = 0; i < regrets.size(); i++) {
      output << regrets[i];
      if (i != regrets.size()-1) output << ", ";
    }
    output << std::endl;
  }
  output.close();
}

void init_logger()
{
  //TODO: Logging setup?
}

fore::Domain test_domain_large(int seed) 
{
  auto horizon(100);
  fore::StateFactory state_fact;
  state_fact.SetResourceAmount(1, 600);
  auto init_state(state_fact.Finish());

  fore::DomainFactory domain_fact(horizon, init_state);

  fore::ExperimentActionTypeFactory exp_act_fact(100, "Experiment", 5, 1000);
  exp_act_fact.SetResourceRequirement(1, 5);
  domain_fact.AddActionType(exp_act_fact.Finish());

  fore::Model cosine(1000, fore::Model::Type::COSINE, seed++);

  domain_fact.AddResource(1, "Budget");
  domain_fact.AddModel(move(cosine));
  domain_fact.set_has_null_action(true);

  return domain_fact.FinishAndReset();
}

fore::Domain test_domain(int seed) 
{
  auto horizon(100);
  fore::StateFactory state_fact;
  state_fact.SetResourceAmount(1, 200);
  auto init_state(state_fact.Finish());

  fore::DomainFactory domain_fact(horizon, init_state);

  fore::ExperimentActionTypeFactory exp_act_fact(100, "Experiment", 5, 1000);
  exp_act_fact.SetResourceRequirement(1, 5);
  domain_fact.AddActionType(exp_act_fact.Finish());

  fore::Model cosine(1000, fore::Model::Type::COSINE, seed++);

  domain_fact.AddResource(1, "Budget");
  domain_fact.AddModel(move(cosine));
  domain_fact.set_has_null_action(true);

  return domain_fact.FinishAndReset();
}
