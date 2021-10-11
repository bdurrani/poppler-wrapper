#include <iostream>
#include "gtest/gtest.h"
#include "helpers.h"

using namespace std;

namespace
{
  TEST(PageCountTest, ReturnsCorrectPageCount)
  {
    EXPECT_EQ(1, GetPageCount("WithActualText.pdf"));
    EXPECT_EQ(1, GetPageCount("rbc.pdf"));
  }
}
