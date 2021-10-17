#include "gtest/gtest.h"
#include "helpers.h"
#include "wrapper/wrapper.h"

namespace
{
  TEST(DocumentLoadingTests, LoadsDocumentsFromFiles)
  {
    auto ptr = ReturnsDocumentPtrFromDisk("WithActualText.pdf");
    EXPECT_NE(ptr, nullptr);
    delete_document(ptr);

    EXPECT_EQ(ReturnsDocumentPtrFromDisk("baddoc.pdf"), nullptr);
  }

  TEST(DocumentLoadingTests, LoadsDocumentsFromBuffer)
  {
    auto ptr = ReturnsDocumentPtrFromBuffer("WithActualText.pdf");
    EXPECT_NE(ptr, nullptr);
    delete_document(ptr);

    EXPECT_EQ(ReturnsDocumentPtrFromBuffer("baddoc.pdf"), nullptr);
  }

  class TextExtractionParamTestFixture : public testing::TestWithParam<std::string>
  {
  };

  TEST_P(TextExtractionParamTestFixture, CorrectlyExtractsTestFromPDFWithPhysicalLayout)
  {
    EXPECT_TRUE(IsPdfExtractionCorrect(GetParam()));
  }

  std::string testFiles[] = {"WithActualText.pdf", "rbc.pdf"};
  INSTANTIATE_TEST_SUITE_P(TextExtractionTests,
                           TextExtractionParamTestFixture,
                           testing::ValuesIn(testFiles));

  TEST(MetadataExtraction, CorrectlyExtractionsCreationDate)
  {
    EXPECT_EQ(1106045198, ReturnsDocumentCreationDate("rbc.pdf"));
  }
}
