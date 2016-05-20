#pragma once

namespace fore {
  class Domain;
}

int main();
void evaluate_switch(const char* ofname, int id1, int id2, int time);
void evaluate_ep_null(const char* ofname, float e);
void evaluate_uniform(const char* ofname, int id);
void init_logger();
fore::Domain create_fake_domain(int seed);
