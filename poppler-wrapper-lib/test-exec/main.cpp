#include <iostream>
#include <cstdlib>
#include "wrapper/wrapper.h"
#include <sys/stat.h>

using namespace std;

inline bool exists(const char *path)
{
  struct stat buffer;
  return (stat(path, &buffer) == 0);
}

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    cout << "No args found" << endl;
    return 1;
  }

  cout << argv[1] << endl;

  if (!exists(argv[1]))
  {
    cout << "File not found" << endl;
  }

  // const char *status = test(argv[1]);
  // cout << status << endl;
  auto doc = create_new_document(argv[1]);
  auto page = document_get_page(doc, 0);
  const char *txt = page_get_text(page);

  cout << txt << endl;
  std::free((void *)txt);
}