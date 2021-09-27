using System;
using System.Runtime.InteropServices;

namespace Poppler.Library
{
	internal static class PopplerNative
	{
		private const string WrapperLibPath = "libwrapper";

		[DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl)]
		public static extern string testingStrings(string input);

		[DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl)]
		public static extern string test(string input);

		[DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr utf8_test(string input);

		[DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr create_new_document(string input);

		[DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl)]
		public static extern int document_get_pagecount(DocumentSafeHandle documentPtr);

		[DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl)]
		public static extern void delete_document(IntPtr documentPtr);

		[DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl)]
		public static extern void delete_page(IntPtr pagePtr);

		[DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr document_get_page(DocumentSafeHandle documentPtr, int pageIndex);

		[DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr page_get_text(PageSafeHandle pagePtr );

    public static string Utf8Test(string filePath)
    {
      var ptr = utf8_test(filePath);
      if(ptr == IntPtr.Zero)
      {
        return string.Empty;
      }
      string? result = Marshal.PtrToStringUTF8(ptr);
      return result ?? string.Empty;
    }

    public static IntPtr CreateDocument(string filePath)
    {
      var docPtr = create_new_document(filePath);
      return docPtr;
    }

    // public static int GetPageCount(IntPtr documentPtr)
    // {
    //   return document_get_pagecount(documentPtr);
    // }
	}
}