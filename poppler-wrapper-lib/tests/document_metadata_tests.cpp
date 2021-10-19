
#include "gtest/gtest.h"
#include "helpers.h"
#include "wrapper/wrapper.h"

namespace
{
  class DateMetdataParamTestFixture : public testing::TestWithParam<std::tuple<std::string, int>>
  {
  };

  TEST_P(DateMetdataParamTestFixture, CorrectlyExtractsCreationDate)
  {
    auto testFileName = std::get<0>(GetParam());
    auto expectedResult = std::get<1>(GetParam());
    EXPECT_EQ(expectedResult, ReturnsDocumentCreationDate(testFileName));
  }

  INSTANTIATE_TEST_SUITE_P(DocumentMetadataExtraction,
                           DateMetdataParamTestFixture,
                           testing::Values(
                               std::make_tuple("rbc.pdf", 1106045198),
                               // missing creation date
                               std::make_tuple("Issue637.pdf", -1),
                               std::make_tuple("metadata.pdf", 1634518185)));

  class AuthorMetdataParamTestFixture : public testing::TestWithParam<std::tuple<std::string, std::string>>
  {
  };

  TEST_P(AuthorMetdataParamTestFixture, CorrectlyExtractsAuthor)
  {
    auto testFileName = std::get<0>(GetParam());
    auto expectedResult = std::get<1>(GetParam());
    auto author = ReturnsDocumentAuthor(testFileName);
    ASSERT_EQ(expectedResult, author);
  }

  INSTANTIATE_TEST_SUITE_P(DocumentMetadataExtraction,
                           AuthorMetdataParamTestFixture,
                           testing::Values(
                               std::make_tuple("WithActualText.pdf", ""),
                               std::make_tuple("metadata.pdf", "Test author")));

  TEST(DocumentMetadataExtraction, DocumentSubject)
  {
    ASSERT_EQ(std::string("Test subjecÿè"), ReturnsDocumentSubject("metadata.pdf"));
  }
}
