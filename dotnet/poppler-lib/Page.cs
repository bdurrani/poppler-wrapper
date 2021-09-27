using System;
using System.Runtime.InteropServices;
using Microsoft.Win32.SafeHandles;

namespace Poppler.Library
{
  internal sealed class PageSafeHandle : SafeHandleZeroOrMinusOneIsInvalid
  {
    public PageSafeHandle(IntPtr handle) : base(true)
    {
      SetHandle(handle);
    }

    protected override bool ReleaseHandle()
    {
      PopplerNative.delete_page(handle);
      return true;
    }
  }

  public class Page: IDisposable
  {
    private readonly PageSafeHandle _pageSafeHandle;

    public Page(IntPtr pagePtr)
    {
      _pageSafeHandle = new PageSafeHandle(pagePtr);
    }

    public string GetText()
    {
      var ptr = PopplerNative.page_get_text(_pageSafeHandle);

      if(ptr == IntPtr.Zero)
      {
        return string.Empty;
      }
      string? result = Marshal.PtrToStringUTF8(ptr);
      return result ?? string.Empty;
    }

    public void Dispose()
    {
      _pageSafeHandle.Dispose();
    }
  }
}