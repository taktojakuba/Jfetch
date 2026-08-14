#include "hostname.h"
#include <fstream>
#include <string>

using namespace std;

string get_hostname()
{
  string hostname;
  ifstream file("/etc/hostname");
  getline(file,hostname);
  return hostname;
}
