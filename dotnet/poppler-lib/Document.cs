using System;

namespace Poppler
{
  public class Document : IDisposable
  {
    private readonly DocumentSafeHandle _documentPtr;

    private Document(IntPtr docPtr)
    {
      _documentPtr = new DocumentSafeHandle(docPtr);
    }

    public int PageCount => PopplerNative.document_get_pagecount(_documentPtr);

    public Page GetPage(int pageNumber)
    {
      var pagePtr = PopplerNative.document_get_page(_documentPtr, pageNumber);
      return new Page(pagePtr);
    }

    public static Document CreateDocument(string path)
    {
      var docPtr = PopplerNative.create_new_document_from_file(path);
      return new Document(docPtr);
    }

    private void Dispose(bool disposing)
    {
      if (!_documentPtr.IsInvalid)
      {
        // Free the handle
        _documentPtr.Dispose();
      }
    }

    public void Dispose()
    {
      Dispose(true);
      GC.SuppressFinalize(this);
    }
  }
}