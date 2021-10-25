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

using Char_Function_Ptr = void (*)(char *);
/**
 * Alias for unique_ptr for a char* buffer with a custom deletion lamda
 */
using Char_Unique_Ptr_With_Deleter = std::unique_ptr<char, Char_Function_Ptr>;

Char_Unique_Ptr_With_Deleter create_unique_ptr_from_text_buffer(char *buffer);

#endif