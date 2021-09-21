#include <memory>
#include "wrapper/wrapper.h"
#include "wrapper/wrapper-private.h"
#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-toc.h>

using namespace poppler;
extern "C"
{
  int test(const char *filePath)
  {
    document *doc = document::load_from_file(filePath, "", "");
    if (!doc)
    {
      return 1;
    }

    return 0;
  }

  int testingStrings(const char *input)
  {
    return 21;
  }
}

bool isDocumentOk(poppler::document *doc)
{
  return true;
}