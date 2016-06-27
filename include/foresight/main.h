#pragma once

#include <string>

namespace fore {
  class Domain;
}

int main(int argc, char* argv[]);
void init_logger();
fore::Domain test_domain_large(int seed);
fore::Domain test_domain(int seed);

