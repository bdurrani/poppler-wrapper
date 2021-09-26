using System;
using System.Runtime.InteropServices;

namespace Poppler.Library
{
    public class Document
    {
      private IntPtr _documentPtr;

      private Document(IntPtr docPtr){
        _documentPtr = docPtr;
      }

      public int PageCount{
        get{
          return PopplerNative.document_get_pagecount(_documentPtr);
        }
      }

      public static Document CreateDocument(string path)
      {
        var docPtr = PopplerNative.create_new_document(path);
        return new Document(docPtr);
      }

    }
}
