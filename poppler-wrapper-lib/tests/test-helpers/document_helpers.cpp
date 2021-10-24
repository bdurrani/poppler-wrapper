#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <memory>
#include "../helpers.h"
#include "wrapper/wrapper.h"
#include "utilities.h"

using namespace std;

auto create_document_unique_ptr_from_file(const std::string &testPdfPath)
{
  auto doc = create_new_document_from_file(testPdfPath.c_str());
  auto lambda_destroyer = [](void *ptr)
  {
    delete_document(ptr);
  };

  std::unique_ptr<void, decltype(lambda_destroyer)> uptr(doc, lambda_destroyer);
  return uptr;
}

void *ReturnsDocumentPtrFromDisk(const string &testDocumentName)
{
  string testPdfPath = GetPathFromTestFileName(testDocumentName);
  return create_new_document_from_file(testPdfPath.c_str());
}

void *ReturnsDocumentPtrFromBuffer(const string &testDocumentName)
{
  string testPdfPath = GetPathFromTestFileName(testDocumentName);

  // https://stackoverflow.com/questions/18398167/how-to-copy-a-txt-file-to-a-char-array-in-c
  std::ifstream input(testPdfPath, ios::binary);
  string contents((istreambuf_iterator<char>(input)),
                  std::istreambuf_iterator<char>());
  return create_new_document_from_buffer(contents.data(), contents.size());
}

int GetPageCount(const string &testDocumentName)
{
  string testPdfPath = GetPathFromTestFileName(testDocumentName);
  auto doc = create_document_unique_ptr_from_file(testPdfPath);
  return document_get_pagecount(doc.get());
}

int ReturnsDocumentCreationDate(const string &testDocumentName)
{
  string testPdfPath = GetPathFromTestFileName(testDocumentName);
  auto doc = create_document_unique_ptr_from_file(testPdfPath);
  auto creationDate = document_get_creation_date(doc.get());
  return creationDate;
}

string ReturnsDocumentAuthor(const string &testDocumentName)
{
  string testPdfPath = GetPathFromTestFileName(testDocumentName);
  auto doc = create_document_unique_ptr_from_file(testPdfPath);
  auto author = document_get_author(doc.get());
  string authorString(author);
  free_text_buffer(author);
  return authorString;
}

string ReturnsDocumentSubject(const string &testDocumentName)
{
  string testPdfPath = GetPathFromTestFileName(testDocumentName);
  auto doc = create_document_unique_ptr_from_file(testPdfPath);
  auto subject = document_get_subject(doc.get());
  string subjectString(subject);
  free_text_buffer(subject);
  return subjectString;
}

string ReturnsDocumentCreator(const string &testDocumentName)
{
  string testPdfPath = GetPathFromTestFileName(testDocumentName);
  auto doc = create_document_unique_ptr_from_file(testPdfPath);
  auto creator = document_get_creator(doc.get());
  string creatorString(creator);
  free_text_buffer(creator);
  return creatorString;
}

bool IsPdfExtractionCorrect(const string &testDocumentName)
{
  string testPdfPath = GetPathFromTestFileName(testDocumentName);
  auto doc = create_document_unique_ptr_from_file(testPdfPath);
  auto pageCount = document_get_pagecount(doc.get());

  std::string documentTxt;
  for (int i = 0; i < pageCount; i++)
  {
    auto page = document_get_page(doc.get(), i);
    const char *txt = page_get_text(page, 0);

    if (txt == nullptr)
    {
      cerr << "Output text was null" << endl;
      delete_page(page);
      return false;
    }

    string strText(txt);
    documentTxt.append(strText);
    free_text_buffer((void *)txt);
    delete_page(page);
  }

  string txtFileName(testDocumentName);
  txtFileName = txtFileName.substr(0, txtFileName.find_last_of('.')) + ".txt";

  auto goldenDatasetPath = BuildGoldenDatasetPath(txtFileName);

  ifstream goldenDataStream(goldenDatasetPath);
  if (goldenDataStream.fail())
  {
    string errMessage("Failed to read golden dataset from ");
    errMessage += goldenDatasetPath;
    throw std::runtime_error(errMessage);
  }

  std::stringstream buffer;
  buffer << goldenDataStream.rdbuf();

  return documentTxt.compare(buffer.str()) == 0;
}