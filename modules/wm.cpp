#include "wm.h"
#include <cstdlib>
#include <string>

using namespace std;

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