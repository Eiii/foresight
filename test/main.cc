#include "gtest/gtest.h"
#include "foresight/test.h"

TEST(MainTest, UnderTen) {
  EXPECT_EQ(test_fn(5), 10);
  EXPECT_EQ(test_fn(2), 4);
  EXPECT_EQ(test_fn(-10), -20);
}

TEST(MainTest, OverTen) {
  EXPECT_EQ(test_fn(12), 6);
  EXPECT_EQ(test_fn(15), 7);
  EXPECT_EQ(test_fn(100), 50);
}
