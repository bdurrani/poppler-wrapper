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

  /**
   * Extracts text from the entire page, based on the layout
   * @param txtLayout Possible values: 0 - physical_layout, 1 - raw_order_layout
   */
  WRAPPER_EXPORT char *page_get_text(void *pagePtr, int txtLayout);

  /**
   * Release the memory associated with the page
   */
  WRAPPER_EXPORT void delete_page(void *pagePtr);

  /**
   * Release the buffer returned by page_get_text()
   */
  WRAPPER_EXPORT void delete_text_buffer(void *txtBuffer);

#ifdef __cplusplus
}
#endif

#endif