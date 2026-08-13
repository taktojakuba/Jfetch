#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;


string get_hostname()
{  
  char hostname[256];
  gethostname(hostname, sizeof(hostname));
  return hostname;
}

string get_osname()
{
  string osname;
  ifstream file("/etc/os-release");
  string line;
  while (getline(file, line))
  {
    if (line.rfind("PRETTY_NAME=", 0) == 0)
      {
        osname = line.substr(12);
        osname = osname.substr(1, osname.size() - 2);
      }
  }
  return osname;
}

string get_kernel()
{
  string kernel;
  ifstream kernel_file("/proc/version");
  string line_ker;
  getline(kernel_file, line_ker);
  kernel = line_ker.substr(14, line_ker.find(' ', 14) - 14);
  return kernel;
}

string get_shell()
{
  string shell;
  string shell_path = getenv("SHELL");
  shell = shell_path.substr(shell_path.find_last_of('/') + 1);
  return shell;
}

string get_wm()
{
  string wm;
  const char* wm_env = getenv("XDG_CURRENT_DESKTOP");
  if (wm_env)
    wm = wm_env;
  else
    wm = "Unknown";
  return wm;
}
string get_term()
{
  string term;
  const char* term_env = getenv("TERM");
  if (term_env)
    term = term_env;
  else
    term = "Unknown";
  return term;
}


int main(int argc, char* argv[])
{
  vector<string> info = {
    "Host: " + get_hostname(),
    "OS: " + get_osname(),
    "Kernel: " + get_kernel(),
    "Shell: " + get_shell(),
    "Term: " + get_term(),
    "WM: " + get_wm()
  };

  if (argc < 2) 
  {
    for(int i = 0;i<info.size();i++){
      cout << info[i] << endl;
    }
    return 0;
  }
  //get file content lines
  ifstream file(argv[1]);
  string line;
  vector<string> lines;
  //push file lines to vector
  while (getline(file, line))
  {
    lines.push_back(line);
  }
  // print out vector with info
  for (size_t i = 0; i < lines.size(); i++)
  {
      cout << lines[i];
      if (i < info.size())
      {
        cout << "  " << info[i];
      }
      cout << endl;
  }
  return 0;
}
