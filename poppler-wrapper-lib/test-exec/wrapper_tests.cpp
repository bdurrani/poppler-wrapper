#include <iostream>
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

  TEST(DocumentLoadingTests, LoadsDocumentsFromFiles)
  {
    auto ptr = ReturnsDocumentPtrFromDisk("WithActualText.pdf");
    EXPECT_NE(ptr, nullptr);
    delete_document(ptr);
    ptr = nullptr;

    EXPECT_EQ(ReturnsDocumentPtrFromDisk("baddoc.pdf"), nullptr);
  }

  TEST(DocumentLoadingTests, LoadsDocumentsFromBuffer)
  {
    auto ptr = ReturnsDocumentPtrFromBuffer("WithActualText.pdf");
    EXPECT_NE(ptr, nullptr);
    delete_document(ptr);
    ptr = nullptr;

    EXPECT_EQ(ReturnsDocumentPtrFromBuffer("baddoc.pdf"), nullptr);
  }
}