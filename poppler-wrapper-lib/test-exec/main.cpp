#include <iostream>
#include <cstdlib>
#include <sys/stat.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
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

static string BuildTestPdfPath(const string &pdfName)
{
  string path(".");
  path += kPathSeparator;
  path += TestFolderName;
  path += kPathSeparator;
  path += pdfName;
  return path;
}

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

inline unsigned int to_uint(char ch)
{
  return static_cast<unsigned int>(static_cast<unsigned char>(ch));
}

// trim from start (in place)
static inline void ltrim(std::string &s)
{
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                  { return !std::isspace(ch); }));
}

// trim from end (in place)
static inline void rtrim(std::string &s)
{
  s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
                       { return !std::isspace(ch); })
              .base(),
          s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s)
{
  ltrim(s);
  rtrim(s);
}

bool comparePdfText(const std::string &data, const std::string &goldenDataPath)
{
  std::ifstream goldenDataStream(goldenDataPath);
  if (goldenDataStream.fail())
  {
    cerr << "Failed to read golden dataset from" << goldenDataPath << endl;
    return false;
  }

  std::stringstream buffer;
  buffer << goldenDataStream.rdbuf();

  cout << "Extracted text" << endl;
  cout << data << endl;

  auto goldenData = buffer.str();
  cout << "Golden text" << endl
       << goldenData << endl;

  cout << endl
       << std::dec << "Data len: " << data.length() << endl;
  cout << "Golden data len: " << buffer.str().length() << endl;

  return data.compare(goldenData) == 0;
}

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    cerr << "Missing args" << endl;
    return 1;
  }

  const char *pdfName = argv[1];

  string testPdfPath = BuildTestPdfPath(pdfName);

  if (!exists(testPdfPath.c_str()))
  {
    cerr << "File not found" << testPdfPath << endl;
    return 1;
  }

  auto doc = create_new_document_from_file(testPdfPath.c_str());
  auto pageCount = document_get_pagecount(doc);

  std::string documentTxt;
  for (int i = 0; i < pageCount; i++)
  {
    auto page = document_get_page(doc, i);
    const char *txt = page_get_text(page);

    if (txt == nullptr)
    {
      cerr << "Output text was null" << endl;
      return 1;
    }
    string strText(txt);
    documentTxt.append(strText);
    delete_text_buffer((void *)txt);
  }

  string txtFileName(pdfName);
  txtFileName = txtFileName.substr(0, txtFileName.find_last_of('.')) + ".txt";

  auto goldenDatasetPath = BuildGoldenDatasetPath(txtFileName);
  bool isSame = comparePdfText(documentTxt, goldenDatasetPath);
  cout << std::boolalpha << "PDFs match: " << isSame << endl;
  if (!isSame)
  {
    cerr << "PDF text output does not match" << endl;
    return 1;
  }
  return 0;
}