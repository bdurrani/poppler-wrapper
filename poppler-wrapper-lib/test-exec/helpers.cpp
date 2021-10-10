#include <unistd.h>
#include <filesystem>
#include "helpers.h"

using namespace std;

std::string GetWorkingDirectory()
{
  char *cwd = get_current_dir_name();
  string workingDir(cwd);
  free(cwd);

  return workingDir;
}
