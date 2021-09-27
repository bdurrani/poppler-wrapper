using System;
using Microsoft.Win32.SafeHandles;

namespace Poppler.Library
{
  internal sealed class DocumentSafeHandle : SafeHandleZeroOrMinusOneIsInvalid
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
}