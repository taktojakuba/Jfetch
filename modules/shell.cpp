#include "shell.h"
#include <cstdlib>
#include <string>

using namespace std;

string get_shell()
{
  string shell;
  string shell_path = getenv("SHELL");
  shell = shell_path.substr(shell_path.find_last_of('/') + 1);
  return shell;
}