#include <memory>
#include "wrapper/wrapper.h"
#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-toc.h>

using namespace poppler;
extern "C"
{
  int test(const char *filePath)
  {
    document *doc = document::load_from_file(filePath, "", "");
    if (doc)
    {
      return 21;
    }
    return 5;
  }

  int testingStrings(const wchar_t *input)
  {
    return 21;
  }
}