#include "kernel.h"
#include <fstream>
#include <string>

using namespace std;

string get_kernel()
{
  string kernel;
  ifstream kernel_file("/proc/version");
  string line_ker;
  getline(kernel_file, line_ker);
  kernel = line_ker.substr(14, line_ker.find(' ', 14) - 14);
  return kernel;
}