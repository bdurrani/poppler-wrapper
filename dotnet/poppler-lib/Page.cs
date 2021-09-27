using System;
using System.Runtime.InteropServices;

namespace Poppler
{
  public class Page: IDisposable
  {
    private readonly PageSafeHandle _pageSafeHandle;

    public Page(IntPtr pagePtr)
    {
      _pageSafeHandle = new PageSafeHandle(pagePtr);
    }

    public string GetText()
    {
      var txtBufferPtr = PopplerNative.page_get_text(_pageSafeHandle);

      if(txtBufferPtr == IntPtr.Zero)
      {
        return string.Empty;
      }
      string? result = Marshal.PtrToStringUTF8(txtBufferPtr);
      PopplerNative.delete_text_buffer(txtBufferPtr);
      return result ?? string.Empty;
    }

    public void Dispose()
    {
      _pageSafeHandle.Dispose();
    }
  }
}