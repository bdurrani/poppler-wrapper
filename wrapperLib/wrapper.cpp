#include <memory>
#include <cstdlib>
#include <string.h>
#include <algorithm> // std::copy
#include <iostream>
#include "wrapper/wrapper.h"
#include "wrapper/wrapper-private.h"
#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-toc.h>
#include <TextOutputDev.h>

#define UNUSED(x) (void)(x)
#define CoTaskMemAlloc(p) malloc(p)
#define CoTaskMemFree(p) free(p)
// EndOfLineKind textEOL = TextOutputDev::defaultEndOfLine();

using namespace poppler;

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

  char *testingStrings(const char *input)
  {
    const char *test = "hello11";

    auto size = strlen(test) + 1;
    char *result = reinterpret_cast<char *>(std::malloc(size));
    strcpy(result, test);
    if (input == nullptr)
    {
      return result;
    }
    const char *another = "boo";
    size = strlen(another) + 1;
    result = reinterpret_cast<char *>(std::malloc(size));
    strcpy(result, another);
    return result;
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
}