#include <memory>
#include <cstdlib>
#include <string.h>
#include <algorithm> // std::copy
#include <iostream>
#include "wrapper/wrapper.h"
#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-toc.h>
#include <poppler-version.h>

#define UNUSED(x) (void)(x)
// #define CoTaskMemAlloc(p) malloc(p)
// #define CoTaskMemFree(p) free(p)

using namespace poppler;
using namespace std;

static std::ostream &operator<<(std::ostream &stream, const poppler::ustring &str)
{
	const poppler::byte_array ba = str.to_utf8();
	for (const char c : ba)
	{
		stream << c;
	}
	return stream;
}

extern "C"
{
	void delete_page(void *pagePtr)
	{
		if (pagePtr == nullptr)
		{
			return;
		}

		auto page = static_cast<poppler::page *>(pagePtr);
		delete page;
	}

	char *page_get_text(void *pagePtr, int textLayoutInt)
	{
		if (!pagePtr)
		{
			return nullptr;
		}

		auto page = static_cast<poppler::page *>(pagePtr);
		auto r = poppler::rectf();

		auto txtLayout = static_cast<page::text_layout_enum>(textLayoutInt);
		cout << "poppler version: " << poppler::version_string() << endl;
		ustring txt = page->text(poppler::rectf(), txtLayout);
		cout << "-----------------------" << endl;
		cout << txt << endl
				 << "------------------------------" << endl;
		auto buffer = txt.to_utf8();
		char *writable = reinterpret_cast<char *>(std::malloc(buffer.size() + 1));
		std::copy(buffer.begin(), buffer.end(), writable);
		writable[buffer.size()] = '\0'; // don't forget the terminating 0
		return writable;
	}

	void free_text_buffer(void *txtBuffer)
	{
		std::free(txtBuffer);
	}
}