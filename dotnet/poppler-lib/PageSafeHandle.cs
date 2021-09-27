using System;
using Microsoft.Win32.SafeHandles;

namespace Poppler
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
}