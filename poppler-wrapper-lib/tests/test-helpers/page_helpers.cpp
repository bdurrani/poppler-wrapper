#include "wrapper/wrapper.h"
#include "page_helpers.h"

Void_Unique_Ptr_With_Deleter create_page_unique_ptr_from_document(void *documentPtr, int pageIndex)
{
  auto page = document_get_page(documentPtr, pageIndex);
  auto page_destroyer = [](void *ptr)
  {
    delete_page(ptr);
  };

  std::unique_ptr<void, decltype(page_destroyer)> uptr(page, page_destroyer);
  return uptr;
}