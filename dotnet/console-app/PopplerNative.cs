using System;
using System.Runtime.InteropServices;

namespace console_app
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

    public static string Utf8Test(string filePath)
    {
      var ptr = utf8_test(filePath);
      if(ptr == IntPtr.Zero)
      {
        return string.Empty;
      }
      string result = Marshal.PtrToStringUTF8(ptr);
      return result;
    }
	}
}