#include "foresight/bayesopt/custommodel.h"

namespace fore {

CustomModel::CustomModel(const vecOfvec& valid_set, bopt_params&& params,
                         Function fn, double epsilon) :
    DiscreteModel(valid_set, params), params_(params), function_(fn), 
    epsilon_(epsilon) {}

CustomModel::~CustomModel()
{
  CustomModel::DeleteParams(&params_);
}

double CustomModel::evaluateSample(const vectord& Xi) 
{
  return function_(Xi);
}

bool CustomModel::checkReachability(const vectord& query)
{
  //TODO: Maybe check that query is in the valid set?
  (void)query;
  return true;
}

bopt_params CustomModel::DefaultParams(int seed)
{
  bopt_params params = initialize_parameters_to_default();

  set_criteria(&params, "cEI");
  params.n_crit_params = 0;

  set_kernel(&params,"kSEISO");
  params.kernel.hp_mean[0] = 1.0;
  params.kernel.hp_std[0] = 1.0;
  params.kernel.n_hp = 1;

  set_mean(&params,"mConst"); //Mean 0, std 0
  params.mean.coef_mean[0] = 0.0;
  params.mean.coef_std[0] = 1.0;
  params.mean.n_coef = 1;

  set_surrogate(&params,"sGaussianProcessML");
  params.noise = 1e-12;

  params.sc_type = SC_MTL; //Kernel parameter learning type
  params.l_type = L_EMPIRICAL;
  params.l_all = 0;

  //TODO this is just so that the initial observations are always the same
  params.random_seed = seed; 
  params.n_iterations = 100; // Number of iterations - Not relevant
  params.n_init_samples = 2;
  params.init_method = 3; //Uniform samples
  params.n_iter_relearn = 100; //TODO ???
  params.force_jump = 0; //Don't jump

  params.verbose_level = -1;

  return params;
}

vecOfvec CustomModel::DefaultValidSet()
{
  //TODO: fill me!
  vecOfvec valid_set;
  for (double x = -1.0; x <= 1.0; x += 0.1) {
    for (double y = -1.0; y < 1.0; y += 0.1) {
      vectord pt(2);
      pt[0] = x; pt[1] = y;
      valid_set.push_back(pt);
    }
  }
  return valid_set;
}

void CustomModel::DeleteParams(bopt_params* params)
{
  delete[] params->kernel.name;
  delete[] params->mean.name;
  delete[] params->log_filename;
  delete[] params->load_filename;
  delete[] params->save_filename;
  delete[] params->surr_name;
  delete[] params->crit_name;
}

CustomModel::Function CustomModel::GetFunction(Model::Type type)
{
  switch (type) {
    case Model::Type::RASTRIGIN:
      return CustomModel::RastriginFn;
      break;
    case Model::Type::ROSENBROCK:
      return CustomModel::RosenbrockFn;
      break;
    case Model::Type::COSINE:
      return CustomModel::CosineFn;
      break;
    default:
      assert(false);
      break;
  }
}

double CustomModel::RastriginFn(const vectord& Xi)
{
  double val;
  val = 3.0 - (1.0 / 3.0) *
        (pow(1.6 * Xi(0) - 0.5, 2.0) +
         pow(1.6 * Xi(1) - 0.5, 2.0) -
         0.3 * cos(3.0 * M_PI * (1.6 * Xi(0) - 0.5)) -
         0.3 * cos(3.0 * M_PI * (1.6 * Xi(1) - 0.5))
        );
  return -val;
}

double CustomModel::RosenbrockFn(const vectord& Xi)
{
  double val;
  val = 3.0 - (1.0 / 3.0) *
        (pow(1.6 * Xi(0) - 0.5, 2.0) +
         pow(1.6 * Xi(1) - 0.5, 2.0) -
         0.3 * cos(3.0 * M_PI * (1.6 * Xi(0) - 0.5)) -
         0.3 * cos(3.0 * M_PI * (1.6 * Xi(1) - 0.5))
        );
  return -val;
}

double CustomModel::CosineFn(const vectord& Xi)
{
  double val;
  val = 3.0 - (1.0 / 3.0) *
        (pow(1.6 * Xi(0) - 0.5, 2.0) +
         pow(1.6 * Xi(1) - 0.5, 2.0) -
         0.3 * cos(3.0 * M_PI * (1.6 * Xi(0) - 0.5)) -
         0.3 * cos(3.0 * M_PI * (1.6 * Xi(1) - 0.5))
        );
  return -val;
}

}
