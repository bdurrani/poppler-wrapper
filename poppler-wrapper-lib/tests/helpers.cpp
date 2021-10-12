#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include "helpers.h"
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

/**
 * Returns true if the file exists
 * @param Fully qualified path to file
 */
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
static string BuildGoldenDatasetPath(const string &pdfName)
{
  string path(".");
  path += kPathSeparator;
  path += TestFolderName;
  path += kPathSeparator;
  path += "golden-data";
  path += kPathSeparator;
  path += pdfName;
  return path;
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

void *ReturnsDocumentPtrFromDisk(const string &testDocumentName)
{
  string testPdfPath = BuildTestPdfPath(testDocumentName);
  if (!exists(testPdfPath.c_str()))
  {
    string errMessage("Test file not found: ");
    errMessage += testDocumentName;
    throw std::runtime_error(errMessage);
  }
  return create_new_document_from_file(testPdfPath.c_str());
}

void *ReturnsDocumentPtrFromBuffer(const string &testDocumentName)
{
  std::string testPdfPath = BuildTestPdfPath(testDocumentName);
  if (!exists(testPdfPath.c_str()))
  {
    string errMessage("Test file not found: ");
    errMessage += testDocumentName;
    throw std::runtime_error(errMessage);
  }

  // https://stackoverflow.com/questions/18398167/how-to-copy-a-txt-file-to-a-char-array-in-c
  std::ifstream input(testPdfPath, ios::binary);
  string contents((istreambuf_iterator<char>(input)),
                  std::istreambuf_iterator<char>());
  return create_new_document_from_buffer(contents.data(), contents.size());
}

bool IsPdfExtractionCorrect(const string &pdfName)
{
  string testPdfPath = BuildTestPdfPath(pdfName);
  if (!exists(testPdfPath.c_str()))
  {
    string errMessage("Test file not found: ");
    errMessage += testPdfPath;
    throw std::runtime_error(errMessage);
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

  string txtFileName(pdfName);
  txtFileName = txtFileName.substr(0, txtFileName.find_last_of('.')) + ".txt";

  auto goldenDatasetPath = BuildGoldenDatasetPath(txtFileName);

  ifstream goldenDataStream(goldenDatasetPath);
  if (goldenDataStream.fail())
  {
    string errMessage("Failed to read golden dataset from");
    errMessage += goldenDatasetPath;
    throw std::runtime_error(errMessage);
  }

  std::stringstream buffer;
  buffer << goldenDataStream.rdbuf();

  return documentTxt.compare(buffer.str()) == 0;
}
