#include "packages.h"
#include <fstream>
#include <string>
#include <dirent.h>
#include <cstdio>
#include <cstdlib>

using namespace std;

// count entries (except hidden ones) in a directory
int count_dir(string path)
{
  int count = 0;
  DIR* dir = opendir(path.c_str());
  if (!dir)
    return -1;
  struct dirent* entry;
  while ((entry = readdir(dir)) != NULL)
  {
    if (entry->d_name[0] != '.')
      count++;
  }
  closedir(dir);
  return count;
}
// count lines in a file that start with a given prefix
int count_matches(string path, string prefix)
{
  int count = 0;
  ifstream file(path);
  string line;
  while (getline(file, line))
  {
    if (line.rfind(prefix, 0) == 0)
      count++;
  }
  return count;
}

// run a command and parse the number it prints
int count_cmd(string cmd)
{
  FILE* pipe = popen(cmd.c_str(), "r");
  if (!pipe)
    return -1;
  char buffer[32];
  int count = -1;
  if (fgets(buffer, sizeof(buffer), pipe))
    count = atoi(buffer);
  pclose(pipe);
  return count;
}

string get_packages()
{
  int count;

  // pacman 
  count = count_dir("/var/lib/pacman/local/");
  if (count > 0)
    return to_string(count) + " (pacman)";

  // dpkg
  count = count_matches("/var/lib/dpkg/status", "Package:");
  if (count > 0)
    return to_string(count) + " (dpkg)";

  // apk
  count = count_matches("/lib/apk/db/installed", "P:");
  if (count > 0)
    return to_string(count) + " (apk)";

  // portage
  count = count_cmd("find /var/db/pkg -mindepth 2 -maxdepth 2 -type d 2>/dev/null | wc -l");
  if (count > 0)
    return to_string(count) + " (portage)";

  // rpm 
  count = count_cmd("rpm -qa 2>/dev/null | wc -l");
  if (count > 0)
    return to_string(count) + " (rpm)";

  // xbps
  count = count_cmd("xbps-query -l 2>/dev/null | wc -l");
  if (count > 0)
    return to_string(count) + " (xbps)";

  // snap
  count = count_dir("/var/lib/snapd/snap/");
  if (count > 0)
    return to_string(count) + " (snap)";

  return "0";
}
