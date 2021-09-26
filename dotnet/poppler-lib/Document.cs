using System;
using System.Runtime.InteropServices;
using Microsoft.Win32.SafeHandles;

namespace Poppler.Library
{
    class DocumentSafeHandle : SafeHandleZeroOrMinusOneIsInvalid
    {
        public DocumentSafeHandle(IntPtr handle)
            : base(true)
        {
            SetHandle(handle);
        }

        protected override bool ReleaseHandle()
        {
            PopplerNative.delete_document(handle);
            return true;
        }
    }

    public class Document
    {
      private DocumentSafeHandle _documentPtr;

      private Document(IntPtr docPtr){
        _documentPtr = new DocumentSafeHandle(docPtr);
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
