#ifndef __WRAPPER_H__
#define __WRAPPER_H__

#include "wrapper_export.h"
#include "wrapper_version.h"

#ifdef __cplusplus
extern "C"
{
#endif

  WRAPPER_EXPORT char *test(const char *filePath);
  WRAPPER_EXPORT char *testingStrings(const char *input);

#ifdef __cplusplus
}
#endif

#endif