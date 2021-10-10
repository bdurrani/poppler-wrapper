#include <iostream>
#include "gtest/gtest.h"
#include "helpers.h"

using namespace std;

namespace
{
  // Demonstrate some basic assertions.
  TEST(HelloTest, BasicAssertions)
  {
    // Expect equality.
    EXPECT_EQ(1, 1);
  }
}
