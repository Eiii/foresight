#include "foresight/gp.h"

#include "foresight/model.h"

#include <cassert>

using std::make_shared;

static vectord point_to_vec(fore::Point p);
static fore::Point vec_to_point(vectord v);

namespace fore {

GP::GP(CustomModel::Function fn, const Model& model, const State& state) :
    model_(CustomModel::DefaultValidSet(),
           CustomModel::DefaultParams(1337),
           fn,
           0.0)
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
  //TODO: Initialize inputs/outputs based on model/state
  auto model_id(model.id());
  const auto& false_obs(state.false_observations().at(model_id));
  const auto& obs(state.observations().at(model_id));
  auto obs_size(false_obs.size()+obs.size());
  auto obs_idx(0);
  vecOfvec inputs(obs_size);
  vectord outputs(obs_size);

  for (const auto& o : false_obs) {
    inputs[obs_idx] = point_to_vec(o.first);
    outputs[obs_idx] = o.second;
    obs_idx++;
  }
  for (const auto& o : obs) {
    inputs[obs_idx] = point_to_vec(o.first);
    outputs[obs_idx] = o.second;
    obs_idx++;
  }
  assert(inputs.size() == obs_size);
  assert(outputs.size() == obs_size);
  model_.initializeOptimizationWithPoints(inputs, outputs);
}

}

static vectord point_to_vec(fore::Point p)
{
  vectord v(p.size());
  std::copy(p.cbegin(), p.cend(), v.begin());
  return v;
}

static fore::Point vec_to_point(vectord v)
{
  fore::Point p(v.size());
  std::copy(v.begin(), v.end(), p.begin());
  return p;
}
