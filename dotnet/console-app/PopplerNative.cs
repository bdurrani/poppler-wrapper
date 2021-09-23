using System.Runtime.InteropServices;

namespace console_app
{
    internal static class PopplerNative
    {
        private const string WrapperLibPath = "libwrapper";
        
        [DllImport(WrapperLibPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int testingStrings(string input);
    }
}