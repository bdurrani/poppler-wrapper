#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <memory>
#include "../helpers.h"
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
const string GoldenDataFolderName = "golden-data";

/**
 * Returns true if the file exists
 * @param Fully qualified path to file
 */
bool exists(const char *path)
{
  struct stat buffer;
  return (stat(path, &buffer) == 0);
}

/**
 * Returns the fully qualified path to the location of the test
 * PDF files
 * @param string Name of the PDF file
 */
string BuildTestPdfPath(const string &pdfName)
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
string BuildGoldenDatasetPath(const string &pdfName)
{
  string path(".");
  path += kPathSeparator;
  path += TestFolderName;
  path += kPathSeparator;
  path += GoldenDataFolderName;
  path += kPathSeparator;
  path += pdfName;
  return path;
}

string GetPathFromTestFileName(const string &testFileName)
{
  string testPdfPath = BuildTestPdfPath(testFileName);
  if (!exists(testPdfPath.c_str()))
  {
    string errMessage("Test file not found: ");
    errMessage += testFileName;
    throw std::runtime_error(errMessage);
  }
  return testPdfPath;
}

std::string GetWorkingDirectory()
{
  char *cwd = get_current_dir_name();
  string workingDir(cwd);
  free(cwd);

  return workingDir;
}