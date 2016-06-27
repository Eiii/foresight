#include "foresight/arbiter.h"

#include <iostream>

using std::move;
using std::cout;
using std::endl;

namespace fore {

Arbiter::Arbiter(const Domain& domain, Policy::Ptr&& policy,
                 RealWorld::Ptr&& real_world, int start_time) :
    domain_(domain), policy_(move(policy)), real_world_(move(real_world)),
    simulator_(domain, real_world_.get()), final_regret_(), 
    start_time_(start_time), last_state_(nullptr) {}

//TODO: Debug output would be nice. Or logging!
void Arbiter::Optimize() 
{
  //cout << "Starting optimization..." << endl;
  real_world_->Start();
  auto current_timestep(start_time_); //TODO: do we always want to start at zero?

  while (!real_world_->IsFinished()) {
    //Wait until the state we want is ready
    while (!real_world_->StateIsReady(current_timestep)) {
      //TODO: sleep plz
    }

    //Get that state, build a list of actions to take
    auto state(real_world_->GetState(current_timestep));
    Action::List actions;

    while (state.time() == current_timestep && 
           simulator_.IsDecisionPoint(state)) {
      auto action_ptr(policy_->SelectAction(state));
      actions.emplace_back(action_ptr->Clone());
      state = simulator_.BeginAction(state, *action_ptr);
    }

    //Execute the calculated actions
    if (actions.size() > 0) {
      //cout << "Executing actions:" << endl;
      for (const auto& action : actions) {
        real_world_->TakeAction(*action);
        //cout << "\t" << action->Info(domain_) << endl;
      }
      //cout << endl;
    }

    //Display current state
    cout << state.Info(domain_) << endl;

    last_state_.reset(new State(state));

    //Move to the next timestep
    current_timestep++;
  }

  real_world_->End();
  //cout << "Finished!" << endl;
  final_regret_ = real_world_->FinalRegret();
}

State Arbiter::CurrentState() const
{
  return *last_state_;
}

bool Arbiter::IsHorizonReached(const State& state) const
{
  return state.time() >= domain_.horizon();
}

}
