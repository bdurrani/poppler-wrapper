using System;
using System.Runtime.InteropServices;

namespace Poppler
{
  public enum TextLayout
  {
    PhysicalLayout = 0,
    RawOrderLayout,
    /// <summary>
    /// Since 0.88
    /// </summary>
    NonRawNonPhysicalLayout
  }

  public class Page : IDisposable
  {
    private readonly PageSafeHandle _pageSafeHandle;

    public Page(IntPtr pagePtr)
    {
      _pageSafeHandle = new PageSafeHandle(pagePtr);
    }

    public string GetText(TextLayout layout)
    {
      var txtBufferPtr = PopplerNative.page_get_text(_pageSafeHandle, (int)layout);

      if (txtBufferPtr == IntPtr.Zero)
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