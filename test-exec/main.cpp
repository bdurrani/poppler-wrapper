#include <iostream>
#include "wrapper/wrapper.h"

using namespace std;

int main(int argc, char *argv[])
{
  std::cout << "Hello cmake" << endl;
  if (argc > 1)
  {
    cout << argv[1] << endl;

    int status = test(argv[1]);
    if (status == 21)
    {
      cout << "Loaded doc" << endl;
    }
    else
    {
      cout << "No doc loaded" << endl;
    }
  }
  else
  {
    cout << "No args found" << endl;
  }
}