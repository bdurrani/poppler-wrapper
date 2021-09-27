## Popper Wrapper for .NET

### About

This is the start of a .NET wrapper about some of the functionality provided
by [Poppler](https://poppler.freedesktop.org/)

Currently it only has support for extracting text from an entire page, one page at a time. 
Support for more functionality will be added as needed. 

### Usage

PopplerWrapper uses the `Dispose` pattern to clean up any unmanaged resources created.

```csharp
using var document = Document.CreateDocument(pdfPath);
var count = document.PageCount;
Console.WriteLine($"Page count: {count}");

// extract text from the first page
using var page = document.GetPage(0);
Console.WriteLine($"{page.GetText()}");
```

## Development

Poppler Wrapper has two parts

### C++ Wrapper

The C++ wrapper is an artisanal C API that flattens the existing stable [C++ Poppler API](https://poppler.freedesktop.org/api/cpp/) so that it can be called via [P/Invoke](https://docs.microsoft.com/en-us/dotnet/standard/native-interop/pinvoke).

More information found [here](./poppler-wrapper/README.md)

### .NET 

Currently I've tested this only on Mac OS and Ubuntu (WSL2) using .NET 5.0.

