#ifndef __WRAPPER_H__
#define __WRAPPER_H__

#include "wrapper_export.h"

#ifdef __cplusplus
extern "C"
{
#endif

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
  WRAPPER_EXPORT void free_text_buffer(void *txtBuffer);

  /**
   * Returns time_t representing the PDF creation date
   */
  WRAPPER_EXPORT int document_get_creation_date(void *documentPtr);

  /**
   * Returns document author
   */
  WRAPPER_EXPORT char *document_get_author(void *documentPtr);

  WRAPPER_EXPORT char *document_get_creator(void *documentPtr);

  WRAPPER_EXPORT char *document_get_subject(void *documentPtr);

#ifdef __cplusplus
}
#endif

#endif