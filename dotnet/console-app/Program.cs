using System;
using System.IO;
using Poppler;

namespace console_app
{
	class Program
	{
		static void Main(string[] args)
		{
      var currentWorkingDir = Directory.GetCurrentDirectory();
      var pdfPath = Path.Join(currentWorkingDir,"assets", "rbc.pdf");
      var testPdfPath = Path.Join(currentWorkingDir,"assets", "test.pdf");

      while (true)
      {
        using var document = Document.CreateDocument(pdfPath);
        var count = document.PageCount;
        Console.WriteLine($"Page count: {count}");
        using var page = document.GetPage(0);
        Console.WriteLine($"{page.GetText()}");

        if(Console.KeyAvailable)
        {
          var key = Console.ReadKey();
          if (key.KeyChar == 'y')
          {
            break;
          }
        }
      }
		}
	}
}
