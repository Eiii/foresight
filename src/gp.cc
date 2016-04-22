#include "foresight/gp.h"

#include "foresight/model.h"

#include <cassert>

using std::make_shared;

namespace fore {

GP::GP(CustomModel::Function fn, const Model& model, const State& state) :
    model_(CustomModel::DefaultValidSet(),
           CustomModel::DefaultParams(1337),
           fn,
           0.000l)
{
  InitializeModel(model, state);
}

std::shared_ptr<GP> GP::GetGP(const Model& model, const State& state)
{
  CustomModel::Function fn(nullptr);
  switch (model.type()) {
    case Model::Type::COSINE:
      fn = CustomModel::CosineFn;
      break;
  }
  assert(fn != nullptr);
  return make_shared<GP>(fn, model, state);
}

Point GP::CalculateBestPoint() const
{
  return vec_to_point(model_.nextPoint());
}

double GP::CalculateMean(Point p) const
{
  return model_.getPrediction(point_to_vec(p))->getMean();
}

double GP::SimulatedResponse(Point p) const
{
  return (model_.function())(point_to_vec(p));
}

void GP::InitializeModel(const Model& model, const State& state)
{
  //Initialize inputs/outputs based on model/state
  auto model_id(model.id());

  //TODO: The 'free' initial obs are temporary. Remove me!
  auto init_obs(model_.getInitialPoints());
  vecOfvec initial_inputs(init_obs.first);
  vectord initial_outputs(init_obs.second);

  //Pre-calculate the final size of our observation list
  //We need to do this in advance since the model might not have any associated
  //observations.
  unsigned int obs_size(0);
  bool has_false_obs(state.false_observations().count(model_id) > 0);
  bool has_obs(state.observations().count(model_id) > 0);

  obs_size += initial_inputs.size();
  if (has_false_obs) {
    obs_size += state.false_observations().at(model_id).size();
  }
  if (has_obs) {
    obs_size += state.observations().at(model_id).size();
  }

  auto obs_idx(0);
  vecOfvec inputs(obs_size);
  vectord outputs(obs_size);

  for (unsigned int i = 0; i < initial_inputs.size(); i++) {
    inputs[obs_idx] = initial_inputs[i];
    outputs[obs_idx] = initial_outputs[i];
    obs_idx++;
  }

  if (has_false_obs) {
    const auto& false_obs(state.false_observations().at(model_id));
    for (const auto& o : false_obs) {
      inputs[obs_idx] = point_to_vec(o.first);
      outputs[obs_idx] = o.second;
      obs_idx++;
    }
  }

  if (has_obs) {
    const auto& obs(state.observations().at(model_id));
    for (const auto& o : obs) {
      inputs[obs_idx] = point_to_vec(o.first);
      outputs[obs_idx] = o.second;
      obs_idx++;
    }
  }
  assert(inputs.size() == obs_size);
  assert(outputs.size() == obs_size);
  model_.initializeOptimizationWithPoints(inputs, outputs);
}

vectord point_to_vec(const fore::Point& p)
{
  vectord v(p.size());
  std::copy(p.cbegin(), p.cend(), v.begin());
  return v;
}

fore::Point vec_to_point(const vectord& v)
{
  fore::Point p(v.size());
  std::copy(v.begin(), v.end(), p.begin());
  return p;
}

}
