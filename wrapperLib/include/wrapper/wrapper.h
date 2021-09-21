#ifndef __WRAPPER_H__
#define __WRAPPER_H__

#include "wrapper_export.h"
#include "wrapper_version.h"

#ifdef __cplusplus
extern "C"
{
#endif

  WRAPPER_EXPORT int test(const char *filePath);
  WRAPPER_EXPORT int testingStrings(const wchar_t *input);

#ifdef __cplusplus
}
#endif

#endif