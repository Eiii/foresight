#include "foresight/resource.h"
#include "gtest/gtest.h"

#include <iostream>

using namespace fore;
using std::cout;
using std::endl;


void resource_eq(Resource::Amount r1, Resource::Amount r2) {
  bool valid = true;
  for (const auto& entry : r1) {
    Resource::Id id(entry.first);
    int amt(entry.second);
    valid = valid && r2[id] == amt;
  }
  for (const auto& entry : r2) {
    Resource::Id id(entry.first);
    int amt(entry.second);
    valid = valid && r1[id] == amt;
  }
  EXPECT_TRUE(valid);
}

TEST(ResourceAmount, Add) {
  //addition to empty
  {
    Resource::Amount amt1{{100, 3}};
    Resource::Amount amt2;
    resource_eq(amt1+amt2, amt1);
  }
  //addition, no shared resources
  {
    Resource::Amount amt1{{100, 3}};
    Resource::Amount amt2{{200, 5}};
    Resource::Amount result{{100, 3}, {200, 5}};
    resource_eq(amt1+amt2, result);
  }
  //addition, shared resources
  {
    Resource::Amount amt1{{15, 2}, {25, 8}};
    Resource::Amount amt2{{7, 2}, {15, 3}};
    Resource::Amount result{{7, 2}, {15, 5}, {25, 8}};
    resource_eq(amt1+amt2, result);
  }
}

TEST(ResourceAmount, Subtract) {
  //subtraction of empty
  {
    Resource::Amount amt1{{100, 3}};
    Resource::Amount amt2;
    resource_eq(amt1-amt2, amt1);
  }
  //subtraction from empty
  {
    Resource::Amount amt1;
    Resource::Amount amt2{{100, 3}};
    Resource::Amount result{{100, -3}};
    resource_eq(amt1-amt2, result);
  }
  //subtraction, shared resources
  {
    Resource::Amount amt1{{15, 2}, {25, 8}, {32, 5}};
    Resource::Amount amt2{{15, 1}, {32, 5}};
    Resource::Amount result{{15, 1}, {25, 8}};
    resource_eq(amt1-amt2, result);
  }
}

TEST(ResourceAmount, Multiply) {
  //multiplication of empty
  {
    Resource::Amount amt1;
    resource_eq(amt1*3, amt1);
  }
  //multiplication by positive
  {
    constexpr int mult(5);
    Resource::Amount amt1{{23, 8}, {12, 2}};
    Resource::Amount result{{23, 8*mult}, {12, 2*mult}};
    resource_eq(amt1*mult, result);
  }
  //multiplication by negative
  {
    constexpr int mult(-2);
    Resource::Amount amt1{{23, 8}, {12, 2}};
    Resource::Amount result{{23, 8*mult}, {12, 2*mult}};
    resource_eq(amt1*mult, result);
  }
}

TEST(ResourceAmount, Divide) {
  //divide by self should be one
  {
    Resource::Amount amt1{{23, 8}, {12, 2}};
    EXPECT_EQ(amt1/amt1, 1);
  }
  //divide by half should be two
  {
    Resource::Amount amt1{{100, 6}, {123, 4}};
    Resource::Amount amt2{{100, 3}, {123, 2}};
    EXPECT_EQ(amt1/amt2, 2);
  }
  //any unshared resources should be zero
  {
    Resource::Amount amt1{{100, 6}, {123, 4}};
    Resource::Amount amt2{{100, 3}, {123, 2}, {200, 1}};
    EXPECT_EQ(amt1/amt2, 0);
  }
  //unshared zero-amount resource shouldn't change the answer
  {
    Resource::Amount amt1{{100, 6}, {123, 4}};
    Resource::Amount amt2{{100, 3}, {123, 2}, {200, 0}};
    EXPECT_EQ(amt1/amt2, 2);
  }
  //integer results only
  {
    Resource::Amount amt1{{100, 13}, {123, 7}};
    Resource::Amount amt2{{100, 4}, {123, 2}};
    EXPECT_EQ(amt1/amt2, 3);
  }
}

TEST(ResourceAmount, has_enough) {
  //should have enough for self
  {
    Resource::Amount required{{23, 8}, {12, 2}};
    EXPECT_TRUE(has_enough(required, required));
  }
  //should have enough when more is available
  {
    Resource::Amount available{{23, 8}, {12, 2}};
    Resource::Amount required{{23, 3}, {12, 1}};
    EXPECT_TRUE(has_enough(available, required));
  }
  //should have enough when more of other resources are available
  {
    Resource::Amount available{{100, 4}, {50, 1}, {75, 10}};
    Resource::Amount required{{50, 1}, {75, 2}};
    EXPECT_TRUE(has_enough(available, required));
  }
  //shouldn't have enough when there isn't enough of a given resource
  {
    Resource::Amount available{{100, 4}, {50, 1}, {75, 10}};
    Resource::Amount required{{50, 1}, {75, 2}};
    EXPECT_TRUE(has_enough(available, required));
  }
}
