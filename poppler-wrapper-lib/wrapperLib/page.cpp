#include <memory>
#include <cstdlib>
#include <string.h>
#include <algorithm> // std::copy
#include <iostream>
#include "wrapper/wrapper.h"
#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler-toc.h>

#define UNUSED(x) (void)(x)
// #define CoTaskMemAlloc(p) malloc(p)
// #define CoTaskMemFree(p) free(p)

using namespace poppler;

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

	char *page_get_text(void *pagePtr)
	{
		if (!pagePtr)
		{
			return nullptr;
		}

		auto page = static_cast<poppler::page *>(pagePtr);

		ustring txt = page->text();
		auto buffer = txt.to_utf8();
		char *writable = reinterpret_cast<char *>(std::malloc(buffer.size() + 1));
		std::copy(buffer.begin(), buffer.end(), writable);
		writable[buffer.size()] = '\0'; // don't forget the terminating 0
		return writable;
	}

	void delete_text_buffer(void *txtBuffer)
	{
		std::free(txtBuffer);
	}
}