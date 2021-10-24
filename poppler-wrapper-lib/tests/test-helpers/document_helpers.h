#ifndef __TEST_HELPERS_DOCUMENT_HELPERS_H__
#define __TEST_HELPERS_DOCUMENT_HELPERS_H__

#include <string>

int GetPageCount(const std::string &pdfName);

void *ReturnsDocumentPtrFromDisk(const std::string &testDocumentName);
void *ReturnsDocumentPtrFromBuffer(const std::string &testDocumentName);

bool IsPdfExtractionCorrect(const std::string &pdfName);
int ReturnsDocumentCreationDate(const std::string &testDocumentName);
std::string ReturnsDocumentAuthor(const std::string &testDocumentName);
std::string ReturnsDocumentSubject(const std::string &testDocumentName);
std::string ReturnsDocumentCreator(const std::string &testDocumentName);

auto create_document_unique_ptr_from_file(const std::string &testDocumentName);

#endif