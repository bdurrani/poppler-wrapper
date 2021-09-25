using System;
using System.IO;

namespace console_app
{
	class Program
	{
		static void Main(string[] args)
		{
			Console.WriteLine("Hello World!");
			var result = PopplerNative.testingStrings("hellp");

      var currentWorkingDir = Directory.GetCurrentDirectory();
      var pdfPath = Path.Join(currentWorkingDir,"assets", "rbc.pdf");
			result = PopplerNative.test(pdfPath);
			Console.WriteLine(result);
			return;
		}
	}
}
