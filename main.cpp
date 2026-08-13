#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <array>

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
  const char* term_env = getenv("TERM_PROGRAM");
  if (term_env)
    term = term_env;
  else
  {
    const char* term_fallback = getenv("TERM");
    term = term_fallback ? term_fallback : "Unknown";
  }
  return term;
}

string get_uptime()
{
  ifstream uptime_file("/proc/uptime");
  double uptime_seconds = 0;
  uptime_file >> uptime_seconds;

  int total_seconds = static_cast<int>(uptime_seconds);
  int hours = total_seconds / 3600;
  int minutes = (total_seconds % 3600) / 60;

  string result;
  if (hours > 0)
    result += to_string(hours) + "h ";
  result += to_string(minutes) + "m";

  return result;
}
int main(int argc, char* argv[])
{
  array<string, 7> info = {
    "Host: " + get_hostname(),
    "OS: " + get_osname(),
    "Kernel: " + get_kernel(),
    "Shell: " + get_shell(),
    "Term: " + get_term(),
    "WM: " + get_wm(),
    "Uptime: " + get_uptime()
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
  size_t i = 0;
  while (getline(file, line)) {
    cout << line;
    if (i < info.size()) {
        cout << "  " << info[i];
    }
    cout << endl;
    ++i;
}
  return 0;
}
