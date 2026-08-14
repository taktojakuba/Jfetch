#include "osname.h"
#include <fstream>
#include <string>

using namespace std;

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
