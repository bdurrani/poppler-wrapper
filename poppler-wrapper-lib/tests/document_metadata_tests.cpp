
#include "gtest/gtest.h"
#include "helpers.h"
#include "wrapper/wrapper.h"

namespace
{

  TEST(DocumentMetadataExtraction, CorrectlyExtractsCreationDate)
  {
    EXPECT_EQ(1106045198, ReturnsDocumentCreationDate("rbc.pdf"));
    // missing creation date
    EXPECT_EQ(-1, ReturnsDocumentCreationDate("Issue637.pdf"));
  }
}