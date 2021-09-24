#include <memory>
#include "wrapper/wrapper.h"
#include "wrapper/wrapper-private.h"
#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-toc.h>
#include <TextOutputDev.h>

#define UNUSED(x) (void)(x)

EndOfLineKind textEOL = TextOutputDev::defaultEndOfLine();

using namespace poppler;
extern "C"
{
  int test(const char *filePath)
  {
    TextOutputDev *textOut;
    bool physLayout = false;
    bool fixedPitch = false;
    bool rawOrder = false;
    bool htmlMeta = false;
    bool discardDiag = false;

    UNUSED(textOut);
    document *doc = document::load_from_file(filePath, "", "");
    if (!doc)
    {
      return 1;
    }

    auto pageCount = doc->pages();
    UNUSED(pageCount);
    textOut = new TextOutputDev("result.txt", physLayout, fixedPitch,
                                rawOrder, htmlMeta, discardDiag);
    if (textOut->isOk())
    {
      textOut->setTextEOL(textEOL);
    }
    delete textOut;
    return 0;
  }

  int testingStrings(const char *input)
  {
    if (input == nullptr)
    {
      return 1;
    }
    return 21;
  }
}