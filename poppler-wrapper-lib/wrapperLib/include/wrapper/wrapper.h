#ifndef __WRAPPER_H__
#define __WRAPPER_H__

#include "wrapper_export.h"

#ifdef __cplusplus
extern "C"
{
#endif

  WRAPPER_EXPORT char *test(const char *filePath);
  WRAPPER_EXPORT char *testingStrings(const char *input);
  WRAPPER_EXPORT char *utf8_test(const char *filePath);

  WRAPPER_EXPORT void *create_new_document_from_file(const char *filePath);
  WRAPPER_EXPORT void *create_new_document_from_buffer(const char *buffer, int bufferLenght);

  WRAPPER_EXPORT void delete_document(void *documentPtr);

  WRAPPER_EXPORT int32_t document_get_pagecount(void *documentPtr);
  WRAPPER_EXPORT void *document_get_page(void *documentPtr, int pageIndex);

  WRAPPER_EXPORT char *page_get_text(void *pagePtr);
  WRAPPER_EXPORT void delete_page(void *pagePtr);

  WRAPPER_EXPORT void delete_text_buffer(void *txtBuffer);

#ifdef __cplusplus
}
#endif

#endif