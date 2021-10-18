
#include "gtest/gtest.h"
#include "helpers.h"
#include "wrapper/wrapper.h"

namespace
{
  TEST(PageCountTest, ReturnsCorrectPageCount)
  {
    EXPECT_EQ(GetPageCount("WithActualText.pdf"), 1);
    EXPECT_EQ(GetPageCount("rbc.pdf"), 1);
  }
}