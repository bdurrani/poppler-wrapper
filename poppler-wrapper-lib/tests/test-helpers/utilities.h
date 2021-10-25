#ifndef __TEST_HELPERS_UTILITIES_H__
#define __TEST_HELPERS_UTILITIES_H__

#include <string>
#include <memory>

bool exists(const char *path);
std::string BuildTestPdfPath(const std::string &);
std::string BuildGoldenDatasetPath(const std::string &);
std::string GetPathFromTestFileName(const std::string &);

using Void_Function_Ptr = void (*)(void *);
using Void_Unique_Ptr_With_Deleter = std::unique_ptr<void, Void_Function_Ptr>;

#endif