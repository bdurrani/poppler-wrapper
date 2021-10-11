#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include "helpers.h"
#include <string>
#include "wrapper/wrapper.h"

using namespace std;

/**
 * Cross platform path separator
 **/
const char kPathSeparator =
#ifdef _WIN32
    '\\';
#else
    '/';
#endif

const string TestFolderName = "test-assets";

static inline bool exists(const char *path)
{
  struct stat buffer;
  return (stat(path, &buffer) == 0);
}

/**
 * Returns the fully qualified path to the location of the test
 * PDF files
 * @param string Name of the PDF file
 */
static string BuildTestPdfPath(const string &pdfName)
{
  string path(".");
  path += kPathSeparator;
  path += TestFolderName;
  path += kPathSeparator;
  path += pdfName;
  return path;
}

/**
 * Returns the fully qualified path to the pdftotext
 * extraction result. 
 * @param string Name of the result file
 */
// static string BuildGoldenDatasetPath(const string &pdfName)
// {
//   string path(".");
//   path += kPathSeparator;
//   path += TestFolderName;
//   path += kPathSeparator;
//   path += "golden-data";
//   path += kPathSeparator;
//   path += pdfName;
//   return path;
// }

std::string GetWorkingDirectory()
{
  char *cwd = get_current_dir_name();
  string workingDir(cwd);
  free(cwd);

  return workingDir;
}

int GetPageCount(const string &pdfName)
{
  string testPdfPath = BuildTestPdfPath(pdfName);
  if (!exists(testPdfPath.c_str()))
  {
    cerr << "Test file not found" << testPdfPath << endl;
    return -1;
  }
  auto doc = create_new_document_from_file(testPdfPath.c_str());
  return document_get_pagecount(doc);
}

bool isPdfExtractionCorrect(const string &pdfName)
{
  string testPdfPath = BuildTestPdfPath(pdfName);
  if (!exists(testPdfPath.c_str()))
  {
    cerr << "Test file not found" << testPdfPath << endl;
    return false;
  }
  auto doc = create_new_document_from_file(testPdfPath.c_str());
  auto pageCount = document_get_pagecount(doc);

  std::string documentTxt;
  for (int i = 0; i < pageCount; i++)
  {
    auto page = document_get_page(doc, i);
    const char *txt = page_get_text(page, 0);

    if (txt == nullptr)
    {
      cerr << "Output text was null" << endl;
      return false;
    }
    string strText(txt);
    documentTxt.append(strText);
    delete_text_buffer((void *)txt);
  }

  return true;
}
