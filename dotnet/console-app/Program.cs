using System;
using System.IO;
using Poppler.Library;

namespace console_app
{
	class Program
	{
		static void Main(string[] args)
		{
			Console.WriteLine("Hello World!");

      var currentWorkingDir = Directory.GetCurrentDirectory();
      var pdfPath = Path.Join(currentWorkingDir,"assets", "rbc.pdf");
      var testPdfPath = Path.Join(currentWorkingDir,"assets", "test.pdf");
			// result = PopplerNative.test(pdfPath);
      // result = PopplerNative.Utf8Test(pdfPath);
			// Console.WriteLine(result);

      // var ptr = PopplerNative.CreateDocument(pdfPath);
      // var count = PopplerNative.GetPageCount(ptr);

      var document = Document.CreateDocument(testPdfPath);
      var count = document.PageCount;
			return;
		}
	}
}
