#include "foresight/main.h"

#include "foresight/actiontype.h"
#include "foresight/domain.h"
#include "foresight/resourcetype.h"

#include <iostream>

int main() {
  //TODO: Parse command line arguments
  //TODO: Load domain
  auto domain(create_fake_domain());
  //TODO: Initialize real world
  //TODO: Create arbiter
  //TODO: Run optimization
  return 0;
}

fore::Domain create_fake_domain() {
  fore::ActionType::Map action_map;
  fore::ResourceType::Map resource_map;

  resource_map.emplace(0, fore::ResourceType(0, "Zero"));

  auto horizon(20);
  return fore::Domain(std::move(action_map), std::move(resource_map), horizon);
}
