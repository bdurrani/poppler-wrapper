using System;
using System.Runtime.InteropServices;

namespace Poppler
{
  internal static class PopplerNative
  {
    private const string WrapperLibPath = "libwrapper";

    [DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    public static extern IntPtr create_new_document_from_file(string input);

    [DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
    public static extern IntPtr create_new_document_from_buffer(byte[] input, int bufferLenght);

    [DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl)]
    public static extern int document_get_pagecount(DocumentSafeHandle documentPtr);

    [DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl)]
    public static extern void delete_document(IntPtr documentPtr);

    [DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl)]
    public static extern void delete_page(IntPtr pagePtr);

    [DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr document_get_page(DocumentSafeHandle documentPtr, int pageIndex);

    [DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr page_get_text(PageSafeHandle pagePtr, int textLayout);

    [DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr free_text_buffer(IntPtr txtBufferPtr);
  }
}