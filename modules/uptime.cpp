#include "uptime.h"
#include <fstream>
#include <string>

using namespace std;

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