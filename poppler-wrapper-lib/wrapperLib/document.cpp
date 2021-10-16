#include <memory>
#include <cstdlib>
#include <string.h>
#include <algorithm> // std::copy
#include <iostream>
#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-toc.h>
#include "wrapper/wrapper.h"
#include "wrapper_version.h"

#define UNUSED(x) (void)(x)
// #define CoTaskMemAlloc(p) malloc(p)
// #define CoTaskMemFree(p) free(p)

using namespace poppler;

char *ustring_to_char(poppler::ustring input);

extern "C"
{
  char *test(const char *filePath)
  {
    document *doc = document::load_from_file(filePath, "", "");
    if (!doc)
    {
      return nullptr;
    }
    std::cerr << "im here" << std::endl;

    auto pageCount = doc->pages();
    UNUSED(pageCount);
    auto page = doc->create_page(0);
    ustring txt = page->text();
    char *writable = reinterpret_cast<char *>(std::malloc(txt.size() + 1));
    std::copy(txt.begin(), txt.end(), writable);
    writable[txt.size()] = '\0'; // don't forget the terminating 0
    return writable;
  }

  char *utf8_test(const char *filePath)
  {
    document *doc = document::load_from_file(filePath, "", "");
    if (!doc)
    {
      return nullptr;
    }
    std::cerr << "im in utf8" << std::endl;

    auto pageCount = doc->pages();
    std::cerr << "page count: " << pageCount << std::endl;
    auto page = doc->create_page(0);
    ustring txt = page->text();
    auto buffer = txt.to_utf8();
    char *writable = reinterpret_cast<char *>(std::malloc(buffer.size() + 1));
    std::copy(buffer.begin(), buffer.end(), writable);
    writable[buffer.size()] = '\0'; // don't forget the terminating 0
    return writable;
  }

  void *create_new_document_from_file(const char *filePath)
  {
    document *doc = document::load_from_file(filePath, "", "");
    if (!doc)
    {
      return nullptr;
    }
    return doc;
  }

  void *create_new_document_from_buffer(const char *buffer, int bufferLenght)
  {
    document *doc = document::load_from_raw_data(buffer, bufferLenght, "", "");
    if (!doc)
    {
      return nullptr;
    }
    return doc;
  }

  void delete_document(void *documentPtr)
  {
    if (documentPtr == nullptr)
    {
      return;
    }

    auto doc = static_cast<document *>(documentPtr);
    delete doc;
  }

  int32_t document_get_pagecount(void *documentPtr)
  {
    auto doc = static_cast<document *>(documentPtr);
    auto pageCount = doc->pages();
    return pageCount;
  }

  void *document_get_page(void *documentPtr, int pageIndex)
  {
    auto doc = static_cast<document *>(documentPtr);
    page *page = doc->create_page(pageIndex);
    return page;
  }

  char *document_get_author(void *documentPtr)
  {
    auto doc = static_cast<document *>(documentPtr);
    auto docAuthor = doc->get_author();
    return ustring_to_char(docAuthor);
  }

  int document_get_creation_date(void *documentPtr)
  {
    auto doc = static_cast<document *>(documentPtr);
    return doc->get_creation_date();
  }
}

char *ustring_to_char(poppler::ustring input)
{
  auto buffer = input.to_utf8();
  char *writable = reinterpret_cast<char *>(std::malloc(buffer.size() + 1));
  std::copy(buffer.begin(), buffer.end(), writable);
  writable[buffer.size()] = '\0'; // don't forget the terminating 0
  return writable;
}