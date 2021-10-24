#ifndef __TEST_HELPERS_UTILITIES_H__
#define __TEST_HELPERS_UTILITIES_H__

#include <string>

bool exists(const char *path);
std::string BuildTestPdfPath(const std::string &);
std::string BuildGoldenDatasetPath(const std::string &);
std::string GetPathFromTestFileName(const std::string &);
std::string GetWorkingDirectory();

#endif