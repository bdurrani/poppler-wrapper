using System.IO;
using NUnit.Framework;
using Poppler;

namespace PopplerTest
{
  public class PdfToTextTests
  {
    [SetUp]
    public void Setup()
    {
    }

    private static object[] _pdfTestCases =
    {
      new object[] { "rbc.pdf", 1 },
      new object[] { "test.pdf", 3 },
    };

    [TestCaseSource(nameof(_pdfTestCases))]
    public void PdfTest(string fileName, int pageCount)
    {
      var currentWorkingDir = Directory.GetCurrentDirectory();
      string assetPath = Path.Join(currentWorkingDir, "assets");
      var pdfPath = Path.Join(assetPath, fileName);
      using var document = Document.CreateDocument(pdfPath);
      Assert.AreEqual(pageCount, document.PageCount);
      string documentText = string.Empty;

      for (int i = 0; i < pageCount; i++)
      {
        using var page = document.GetPage(i);
        documentText += page.GetText(TextLayout.PhysicalLayout);
      }

      var fileNameOnly = Path.GetFileNameWithoutExtension(fileName);
      var goldenPath = Path.Join(assetPath, "golden-data", $"{fileNameOnly}.txt");
      var goldenData = File.ReadAllText(goldenPath);
      Assert.AreEqual(goldenData, documentText);
    }
  }
}