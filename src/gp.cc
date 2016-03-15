#include "foresight/gp.h"

#include "foresight/model.h"

namespace fore {

GP::GP(const Model& model, const State& state)
{
  (void)model;
  (void)state;
  //TODO: Initialize stuff based on model and state...
}

GP GP::GetGP(const Model& model, const State& state)
{
  return GP(model, state);
}

Point GP::CalculateBestPoint() const
{
  Point p = {0.0, 0.0};
  return p;
}

}
