#pragma once

#include <string>

namespace fore {
  class Domain;
}

int main();
void evaluate_uniform(std::string ofname, int id1);
void init_logger();
fore::Domain test_domain_large(int seed);
