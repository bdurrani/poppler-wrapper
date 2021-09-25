#include <memory>
#include <cstdlib>
#include <string.h>
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
  int test(const char *filePath)
  {
    // TextOutputDev *textOut;
    // bool physLayout = false;
    // bool fixedPitch = false;
    // bool rawOrder = false;
    // bool htmlMeta = false;
    // bool discardDiag = false;
    // double resolution = 72.0;

    // UNUSED(textOut);
    document *doc = document::load_from_file(filePath, "", "");
    if (!doc)
    {
      return 1;
    }

    auto pageCount = doc->pages();
    UNUSED(pageCount);
    auto page = doc->create_page(0);
    ustring txt = page->text();
    return 0;
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
}