#ifndef __TEST_HELPERS_DOCUMENT_HELPERS_H__
#define __TEST_HELPERS_DOCUMENT_HELPERS_H__

#include <string>
#include "utilities.h"

int GetPageCount(const std::string &pdfName);

void *ReturnsDocumentPtrFromDisk(const std::string &testDocumentName);
void *ReturnsDocumentPtrFromBuffer(const std::string &testDocumentName);

bool IsPdfExtractionCorrect(const std::string &pdfName);
int ReturnsDocumentCreationDate(const std::string &testDocumentName);
std::string ReturnsDocumentAuthor(const std::string &testDocumentName);
std::string ReturnsDocumentSubject(const std::string &testDocumentName);
std::string ReturnsDocumentCreator(const std::string &testDocumentName);
std::string ReturnsDocumentKeywords(const std::string &testDocumentName);
std::string ReturnsDocumentProducer(const std::string &testDocumentName);

Void_Unique_Ptr_With_Deleter create_document_unique_ptr_from_file(const std::string &testDocumentName);

#endif