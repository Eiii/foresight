#pragma once

#include <string>

namespace fore {
  class Domain;
}

int main();
void evaluate_upfront(std::string ofname, int id1, int id2);
void init_logger();
fore::Domain create_fake_domain(int seed);
