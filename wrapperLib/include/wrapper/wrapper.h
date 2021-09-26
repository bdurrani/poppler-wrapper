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
  WRAPPER_EXPORT char *utf8_test(const char *filePath);

  WRAPPER_EXPORT void *create_new_document(const char *filePath);
  WRAPPER_EXPORT int document_get_pagecount(void *documentPtr);

#ifdef __cplusplus
}
#endif

#endif